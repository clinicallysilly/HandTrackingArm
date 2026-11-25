# only execute the following code every 3 frames
def onFrameEnd(frame):
    if frame % 3 != 0:
        return
    chop = op('outgoing_data') # declare which chop the data is coming from
    # find rounded values for each chop null
    x = int(round(chop['x'].eval()))
    y = int(round(chop['y'].eval()))
    g = int(round(chop['grip'].eval()))
    op('serial1').send(f"{x},{y},{g}\n", terminator='') # Send a message to the serial monitor with values to parse

    # IMPORTANT! While working on arduino_pt2, replace {y} with the two startup values for the arm and wrist position, such as 90,60
