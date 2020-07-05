#!/usr/bin/env python


# TODO
# [√] read serial monitor
# [√] handle begin/end statements to control the data reading
# [√] upon end -> write to excel or csv file
# [√] during reading, plot live data
# [√] upon end -> save plot
# [X] handle user input (they need to specify serial port)

import sys
import serial
import numpy as np
import pandas as pd
import datetime as dt
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


global data, doneReading, ser


def init_connection():
    ''' initialize serial port connection '''
    try:
        serial_port = sys.argv[1]
    except IndexError:
        serial_port = '/dev/cu.usbmodem14101'
    ser = serial.Serial(serial_port, baudrate=9600, timeout=100)
    return ser


def read_serial_data():
    ''' read and parse serial data '''
    global doneReading, data
    line = ser.readline().decode()
    print(line)
    if "Begin skyread" in line:
        # clear data? and plot?
        pass
    elif "End skyread" in line:
        doneReading = True
    elif doneReading:
        line_data = np.array([np.fromstring(line, sep='\t')])
        if data is None:
            data = line_data
        data = np.append(data, line_data, axis=0)
    return doneReading


def plot_ani(i):
    global doneReading
    doneReading = read_serial_data()
    if doneReading:
        save_and_quit()
    if data is not None:
        plt.cla()
        plt.plot(data[:, 1], data[:, 2])
        plt.tight_layout()


def save_and_quit():
    # get datetime
    dt_str = dt.datetime.now().strftime('%d%m%Y_at_%H%M%S')
    # save figure
    figfile = 'skyread_{}.png'.format(dt_str)
    plt.savefig(figfile)
    plt.close()
    # save data
    csvfile = 'skyread_{}.csv'.format(dt_str)
    df = pd.DataFrame(data)
    df.columns = ['mx', 'my', 'r0', 'r1', 'r2', 'r3', 'r2-r0', 'r3-r1']
    df.to_csv(csvfile)
    # quit
    print("Done! :)")
    sys.exit(0)


def main():
    '''
    python script to read data from serial monitor, display and save it
    '''
    global data, doneReading, ser
    data = None
    doneReading = False
    # establish serial connection
    ser = init_connection()
    # animation
    plt.style.use('seaborn-paper')
    ani = FuncAnimation(plt.gcf(), plot_ani, interval=100)
    plt.show()


if __name__ == '__main__':
    # global variables
    main()
