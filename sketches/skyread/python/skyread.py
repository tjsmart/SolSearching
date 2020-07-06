#!/usr/bin/env python


import sys
import serial
import numpy as np
import pandas as pd
import datetime as dt
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import argparse


global data, doneReading, ser


def parse_command_line():
    ''' parse command line options '''
    parser = argparse.ArgumentParser(
        description="User in conjuction with skyread.ino to record data to csv and plot in real-time"
    )
    parser.add_argument(
        'serial_port', metavar='serial_port', type=str, help="the name of the serial port arduino is connected to"
    )
    return parser.parse_args()


def read_serial_data():
    ''' read and parse serial data '''
    global doneReading, data, ser
    line = ser.readline().decode()
    print(line)
    if "Begin skyread" in line:
        # clear data? and plot?
        return
    elif "End skyread" in line:
        doneReading = True
        return
    # read data
    line_data = np.array([np.fromstring(line, sep='\t')])
    if data is None:
        data = line_data
    else:
        data = np.append(data, line_data, axis=0)


def plot_animation(i):
    global doneReading, data
    read_serial_data()
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
    # parse command line arguments
    args = parse_command_line()
    # establish serial connection
    ser = serial.Serial(args.serial_port, baudrate=9600, timeout=100)
    # animation
    plt.style.use('seaborn-paper')
    ani = FuncAnimation(plt.gcf(), plot_animation, interval=100)    # noqa:F841
    plt.show()


if __name__ == '__main__':
    # global variables
    main()
