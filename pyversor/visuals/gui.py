from vispy import io
from vispy import scene, visuals
from vispy.visuals.transforms import MatrixTransform, STTransform

import datetime
import time
import threading
import pickle
import zmq

import numpy as np

from pyversor import *

canvas = scene.SceneCanvas(keys='interactive', bgcolor='white',
                        size=(1920,1080), show=True)
view = canvas.central_widget.add_view()
view.camera = 'arcball'
scene.visuals.XYZAxis(parent=view.scene)

Plot3D = scene.visuals.create_visual_node(visuals.LinePlotVisual)

def on_key_press(event):
    if event.key.name == 'S':
        filename = '{}-pyversor-screenshot.png'.format(datetime.datetime.now().isoformat())
        screenshot = canvas.render()
        io.write_png(filename, screenshot)
        print('Saved screenshot with filename: {}'.format(filename))

canvas.connect(on_key_press)

def draw_point(point):
    pos = [point[0], point[1], point[2]]
    p = scene.visuals.Sphere(radius=0.01, parent=view.scene)
    p.transform = STTransform(translate=pos)

def draw_line(line):
    pos = [[p[0], p[1], p[2]] for p in line]
    Plot3D(pos, width=2.0, parent=view.scene)
    # Plot3D(pos, width=2.0, color='red',
    #    edge_color='w', symbol='o', face_color=(0.2, 0.2, 1, 0.8),
    #    parent=view.scene)


def draw(drawable):
    if isinstance(drawable, list):
        draw_line(drawable)

def worker():
    port = "5556"
    context = zmq.Context()
    socket = context.socket(zmq.PAIR)
    socket.bind("tcp://127.0.0.1:%s" % port)
    while True:
        msg = socket.recv()
        a = pickle.loads(msg)
        draw(a)
        time.sleep(0.05)

if __name__ == '__main__':
    thread = threading.Thread(target=worker)
    thread.daemon = True
    thread.start()
    canvas.app.run()