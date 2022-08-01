import serial
import json
import keyboard
import traceback
import logging
import sqlite3

def write_json_to_database(data, database):
    cur = database.cursor()
    
    cur.execute("INSERT or IGNORE INTO location_time(lat,lon,timestamp,boat_id) VALUES (?, ?, ?, ?)", (data["lat"], data["lon"], data["time"], data["boat"]))
    location_id = cur.lastrowid

    cur.execute("INSERT or IGNORE INTO dissolved_solids(ppm,locationtime_id) VALUES (?, ?)", (data["tds"], location_id))
    cur.execute("INSERT or IGNORE INTO ph(level,locationtime_id) VALUES (?, ?)", (data["ph"], location_id))
    cur.execute("INSERT or IGNORE INTO temperature(degree,locationtime_id) VALUES (?, ?)", (data["temp"], location_id))
    database.commit()

if __name__ == "__main__":
    # Set log file to log errors/info to, reset all previous info
    log_dummy = open("serial.log", "w")
    log_dummy.write("")
    log_dummy.close()
    logging.basicConfig(filename='serial.log', encoding='utf-8', level=logging.DEBUG)
    # Serial reading vars
    log_index = 0
    database_broken = False
    try:
    	ser = serial.Serial('COM6', 9600)
    except Exception as e:
            logging.error(traceback.format_exc())
    # Raw data output file
    raw_savefile = open("raw_data.txt", "a")
    # Reset json data store, then open it again for appending
    results_json = open("results_json.txt", "w")
    results_json.write("")
    results_json.close()
    
    results_json = open("results_json.txt", "a")
    database = None
    # Try to open database, never use database again if fails
    try:
        database = sqlite3.connect("2022Cosmos13Data.db")
    except Exception as ex:
        logging.error(traceback.format_exc())
        database_broken = True
    # Data reading loop, end at 'q' pressed
    while not keyboard.is_pressed('q'):
        try:
            if(ser.in_waiting > 0):
                print("ROGER ROGER")
                # Read raw serial data line from microcontroller, write to raw data file, then index
                raw_data = ser.readline()
                raw_savefile.write(str(raw_data) + "\n")
                log_index += 1
                # Isolate json from raw_data
                data = json.loads(raw_data)
                # Write json to file record
                results_json.write(str(data) + "\n")
                # Log every fifth json read
                if log_index % 5 == 0:
                    logging.debug(str(log_index) + "th json line read")
                # Try to write to the database if it isn't broken
                if not database_broken:
                    try:
                        write_json_to_database(data, database)
                    except Exception as excp:
                        # Database breaks, stop sending to it
                        logging.error(traceback.format_exc())
                        database_broken = True
        # Note errors in json manipulation
        except Exception as e:
            logging.error(traceback.format_exc())
    # Close results json file
    results_json.close()
    # Close database
    if not database_broken:
        database.close()
    # Close raw data file
    raw_savefile.close()

