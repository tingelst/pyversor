from vispy import io
from vispy import scene, visuals
from vispy.visuals.transforms import MatrixTransform, STTransform

import datetime
import time
import threading
import pickle
import zmq

from pyversor import *

canvas = scene.SceneCanvas(keys='interactive', bgcolor='white',
                        size=(1920,1080), show=True)
view = canvas.central_widget.add_view()
view.camera = 'arcball'
scene.visuals.XYZAxis(parent=view.scene)

Ellipse3D = scene.visuals.create_visual_node(visuals.EllipseVisual)

def on_key_press(event):
    # modifiers = [key.name for key in event.modifiers]
    # print('Key pressed - text: %r, key: %s, modifiers: %r' % (
    #     event.text, event.key.name, modifiers))
    if event.key.name == 'A':
        # print(dir(view.scene))
        print(view.scene.children)
        Ellipse3D([0,0,0], parent=view.scene, radius=2.5, border_color='r', color=(0,0,0,0.5))
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

def draw(drawable):
    if isinstance(drawable, list):
        print('Received list of {} objects'.format(len(drawable)))
        for item in drawable:
            draw_point(item)

def worker():
    print('Starting GUI')
    port = "5556"
    context = zmq.Context()
    socket = context.socket(zmq.PAIR)
    socket.bind("tcp://*:%s" % port)
    while True:
        print('running')
        msg = socket.recv()
        print(msg)
        a = pickle.loads(msg)
        draw(a)
        time.sleep(0.1)


if __name__ == '__main__':
    thread = threading.Thread(target=worker)
    thread.daemon = True
    thread.start()
    canvas.app.run()