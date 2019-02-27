import matplotlib.pyplot as plt
import numpy as np
import plotly.plotly as py
import plotly.graph_objs as go
import cufflinks
from plotly.offline import  init_notebook_mode, plot, iplot

init_notebook_mode(connected=True)
%matplotlib inline





def show_table(array, title=""):
    """
        Show values of a table in different colors each
    Args:
        array (np.ndaray): 2 array with integer values
        title (str): title
    """
    fig, ax = plt.subplots()
    ax.imshow(array)
    ax.set_title(title);

def plotly_show_table(array, showscale=False):
    """
        Return heatmap for table values
    Args:
        array (np.array): 
        showscale (boolean)
    """
    trace = go.Heatmap(z=array[::-1], showscale=showscale)
    data=[trace]
    iplot(data)
