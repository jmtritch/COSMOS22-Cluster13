import sqlite3
import pandas as pd
import numpy as np
import plotly.express as px
import plotly.graph_objects as go
import dash
from dash import Dash, dash_table
from dash import dcc
from dash import html
from dash.dependencies import Input, Output, State
import plotly.io as pio

con = sqlite3.connect('MergedDataFirstAndSecondHalves/MIRAMAR_trial_FULL.db') #create the SQLite connection with the database file
#cur = con.cursor() #create the local cursor for the connection

#SQL code to access columns from the db file
sql = '''
SELECT lt.id, lt.boat_id AS boat, lt.timestamp, lt.lat, lt.lon, p.level AS ph, temp.degree AS temp, ds.ppm AS tds
FROM location_time AS lt
LEFT JOIN ph AS p 
ON lt.id = p.locationtime_id
LEFT JOIN temperature AS temp 
ON lt.id = temp.locationtime_id
LEFT JOIN dissolved_solids AS ds 
ON lt.id = ds.locationtime_id
ORDER BY lt.id DESC;
'''

#use the connection with the database to read the SQL code and create a dataframe in the format the SQL code describes
df_1 = pd.read_sql(sql, con)
#print(df_1.head()) debugging code

#create a scatterplot map figure from the dataframe data
fig = px.scatter_mapbox(df_1, lat="lat", lon="lon", hover_data=["id", "ph", "temp", "tds"], height=600, color="boat", mapbox_style="open-street-map")
fig.update_layout(margin={"r":0,"t":0,"l":0,"b":0}) #right, top, left, and bottom margins

app = Dash(__name__)

#layout of dashboard
app.layout = html.Div([ 
    #division for the 3 graphs
    html.Div(children=[
        #ph graph
        dcc.Graph(
            id="phgraph", style={'display': 'inline-block', 'width': '33%'},
            figure={
                "data": [
                    {
                        "x": df_1["timestamp"], #x-axis is timestamp
                        "y": df_1["ph"], #y-axis is ph
                        "name" : "pH",
                        "type": "line",
                        "marker": {"color": "#f3f57f"}, #color of graph
                    },
                ],
                "layout": {
                    "showlegend": True,

                    "xaxis": {
                        "automargin": True,
                        "title": {"text": "Timestamp"}
                    },
                    "yaxis": {
                        "automargin": True,
                        "title": {"text": "pH"}
                        },
                    "height": 400,
                    "margin": {"t": 10, "l": 10, "r": 10},
                },
            }
        ),
        #temperature graph
        dcc.Graph(
            id="tempgraph", style={'display': 'inline-block', 'width': '33%'},
            figure={
                "data": [
                    {
                    "x": df_1["timestamp"], #x-axis is timestamp
                    "y": df_1["temp"], #y-axis is temp
                    "name" : "temp",
                    "type": "line",
                    "marker": {"color": "#e0553d"}, #color of graph
                    },
                ],
                "layout": {
                    "showlegend": True,

                    "xaxis": {
                        "automargin": True,
                        "title": {"text": "Timestamp"}
                    },
                    "yaxis": {
                        "automargin": True,
                        "title": {"text": "Temperature (°C)"}
                        },
                    "height": 400,
                    "margin": {"t": 10, "l": 10, "r": 10},
                },
            }
        ),
        #tds graph
        dcc.Graph(
            id="tdsgraph", style={'display': 'inline-block', 'width': '33%'},
            figure={
                "data": [
                    {
                    "x": df_1["timestamp"], #x-axis is timestamp
                    "y": df_1["tds"], #y-axis is tds
                    "name" : "tds",
                    "type": "line",
                    "marker": {"color": "#7ff5e3"}, #color of graph
                    },
                ],
                "layout": {
                    "showlegend": True,

                    "xaxis": {
                        "automargin": True,
                        "title": {"text": "Timestamp"}
                    },
                    "yaxis": {
                        "automargin": True,
                        "title": {"text": "Total Dissolved Solids (ppm)"}
                        },
                    "height": 400,
                    "margin": {"t": 10, "l": 10, "r": 10},
                },
            }

        ), 
    ]),
    # create map using the figure created earlier
    dcc.Graph(id='map',figure=fig), 
    # create datatable to display the dataframe
    dash_table.DataTable(df_1.to_dict('records'),
        id='data_table',
        columns=[{'id':c, 'name':c} for c in df_1.columns],
        fixed_rows={'headers': True},
        page_size=10
    ),
    html.Div(id='output_div') #cell selected from the datatable
]) 

#callback for the user clicks on the dataframe cells
@app.callback(
    Output('output_div', 'children'),
    Input('data_table', 'active_cell'),
    State('data_table', 'data')
)
def getActiveCell(active_cell, data):
    if active_cell:
        col = active_cell['column_id']
        row = active_cell['row']
        cellData = data[row][col]
        return html.P(f'row: {row}, col: {col}, value: {cellData}')
    return html.P('no cell selected')

if __name__ == '__main__':
    app.run_server(debug=True)
