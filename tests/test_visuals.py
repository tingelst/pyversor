import sys
sys.path.append('build')

import numpy as np
import numpy.random as rnd


import zmq
import random
import sys
import time

import pickle

from pyversor_ import ega, cga
from pyversor_.cga.round import null

import datetime

from vispy import io
from vispy import scene, visuals
from vispy.gloo.util import _screenshot as screenshot
from vispy.visuals.transforms import MatrixTransform, STTransform

ega.Vector(1,2,3).dual()

canvas = scene.SceneCanvas(keys='interactive', bgcolor='white',
                           size=(1920,1080), show=True, dpi=1000)

view = canvas.central_widget.add_view()
view.camera = 'arcball'

Ellipse3D = scene.visuals.create_visual_node(visuals.EllipseVisual)
circle_visual = Ellipse3D([0,0,0], radius=2.5, border_color='r', color=(0,0,0,0.5))

objects = []



a = cga.construct.sphere(null(ega.Vector(0,0,0)), 0.5)
pos_a = cga.round.location(a)
pos_a = np.array(pos_a)[:3]
b = cga.construct.sphere(null(ega.Vector(0,-0.75,0)), 0.5)
pos_b = cga.round.location(b)
pos_b = np.array(pos_b)[:3]

print(a ^ 3.0)
print(5.0 ^ a)

m = cga.generate.exp(cga.DualLine(*rnd.randn(6)))
print(a)
print(a.spin(m))

# InfiniteLine3D = scene.visuals.create_visual_node(visuals.InfiniteLineVisual)
# InfiniteLine3D(pos = 1, parent=view.scene, color=(1,0,0,1))


circle = cga.construct.meet(a,b)


pos = cga.round.location(circle)
pos = np.array(pos)[:3]
aa = cga.operate.axis_angle(circle)
aa = np.array(aa)
radius = cga.round.radius(circle)

circle_visual = Ellipse3D([0,0,0], radius=radius, parent=view.scene, border_color='r', color=(0,0,0,0))
# circle_visual.border.method = 'agg'
# circle_visual.border.set_data(width=2)

m = MatrixTransform()
m.rotate(aa[0], aa[1:])
m.translate(pos)

circle_visual.transform = m

m = MatrixTransform()
m.rotate(45, [1,0,0])
m.translate([1,2,3])

# print(m.matrix.T)

sphere1 = scene.visuals.Sphere(radius=cga.round.radius(a), method='latitude', parent=view.scene, color=(0.1,0.2,0.3,1),
                               edge_color=None)

sphere1.transform = STTransform(translate=pos_a)

sphere2 = scene.visuals.Sphere(radius=cga.round.radius(b), method='latitude', parent=view.scene,  color=(0.3,0.2,0.1,1),
                               edge_color=None)
sphere2.transform = STTransform(translate=pos_b)

# sphere3 = scene.visuals.Sphere(radius=radius(c), rows=10, cols=10, depth=10,
#                                method='cube', parent=view.scene,
#                                edge_color='black')

base = scene.visuals.XYZAxis(parent=view.scene)
# frame = scene.visuals.XYZAxis(parent=view.scene, antialias=True)
# frame.transform = m


# view.camera.set_range(x=[-3, 3])

# im = screenshot((0,0,canvas.size[0], canvas.size[1]))
# im = np.array(im)

# Add some text instructions
# text = scene.visuals.Text("Drag right mouse button to zoom.", 
#                           color='b',
#                           anchor_x='left',
#                           parent=view,
#                           pos=(20, 30))
# # im[:, :, 3] = 255
# print(im)


import threading
def worker():
    port = "5556"
    context = zmq.Context()
    socket = context.socket(zmq.PAIR)
    socket.bind("tcp://*:%s" % port)
    while True:
        socket.send_string("Server message to client3")
        msg = socket.recv()
        a = pickle.loads(msg)
        print(a)
        time.sleep(1)

thread = threading.Thread(target=worker)
thread.start()

def on_key_press(event):
    # modifiers = [key.name for key in event.modifiers]
    # print('Key pressed - text: %r, key: %s, modifiers: %r' % (
    #     event.text, event.key.name, modifiers))
    if event.key.name == 'A':
        # print(dir(view.scene))
        print(view.scene.children)
        objects.append(Ellipse3D([0,0,0], parent=view.scene, radius=2.5, border_color='r', color=(0,0,0,0.5)))
    if event.key.name == 'S':
        filename = '{}-pyversor-screenshot.png'.format(datetime.datetime.now().isoformat())
        screenshot = canvas.render()
        io.write_png(filename, screenshot)
        print('Saved screenshot with filename: {}'.format(filename))

canvas.connect(on_key_press)


if __name__ == '__main__' and sys.flags.interactive == 0:
    canvas.app.run()
