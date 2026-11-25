# Only execute the following code every 4 frames
def onFrameEnd(frame):
    if frame % 3 != 0:
        return
        
    chop = op('outgoing_data') # declare which CHOP you are taking data from
    x = int(round(chop['x'].eval())) # round values from x pos null
    g = int(round(chop['grip'].eval())) # same with grip null
    op('serial1').send(f"{x},90,60,{g}\n", terminator='') # Send a string to the serial monitor with the changing variables while keeping the arm angles constant
