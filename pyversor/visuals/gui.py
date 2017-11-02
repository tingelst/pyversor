
from vispy import app, io, scene, visuals
from vispy.visuals.transforms import MatrixTransform, STTransform

import datetime
import time
import threading
import pickle
import zmq

import numpy as np

# canvas = scene.SceneCanvas(keys='interactive', bgcolor='white',
#                            size=(800, 600), show=True)

# view = canvas.central_widget.add_view()
# view.camera = 'arcball'


# Plot3D = scene.visuals.create_visual_node(visuals.LinePlotVisual)


# def draw_sphere(msg):
#     pos = msg['translation']
#     radius = msg['radius']
#     color = msg['color']
#     sphere = scene.visuals.Sphere(radius=radius, color=color)
#     sphere.transform = STTransform(translate=pos)
#     view.add(sphere)
#     objects.append(sphere)

# # def draw_line(msg):
# #     pos = np.array([pos, [0, 0, 0]])
# #     arrow = scene.visuals.Arrow()
# #     arrow.set_data(pos=pos, color=color, arrows=pos)
# #     view.add(arrow)
# #     objects.append(arrow)


# objects = []


# def draw_scatter(points):
#     scatter = scene.visuals.Markers()
#     scatter.set_data(points, edge_color=None, face_color=(1, 1, 1, .5), size=5)
#     view.add(scatter)
#     objects.append(scatter)


# def draw_path(msg):
#     pos = msg['path']
#     print(pos.shape)
#     color = msg['color']
#     path = Plot3D(pos, parent=view.scene)
#     # path = Plot3D(pos, width=2.0, color=color,
#     #               edge_color='w', symbol='o', face_color=(0.2, 0.2, 1, 0.8),
#     #               parent=view.scene)
#     objects.append(path)


# def clear_view():
#     global objects
#     for obj in objects:
#         obj.parent = None
#     objects = []


# canvas.connect(on_key_press)


class Gui(scene.SceneCanvas):
    def __init__(self, **kwargs):
        scene.SceneCanvas.__init__(
            self, title='pyversor', keys='interactive', bgcolor='white', size=(800, 600), show=True)

        self.unfreeze()

        self.view = self.central_widget.add_view()
        self.view.camera = 'turntable'

        self._worker_thread = threading.Thread(target=self.worker)
        self._worker_thread.daemon = True
        self._worker_thread.start()

        self._base_frame = scene.visuals.XYZAxis()

        self._objects = []

        self.freeze()

    def clear_view(self):
        for obj in self._objects:
            obj.parent = None
        objects = []

    def on_key_press(self, event):
        if event.key.name == 'S':
            filename = '{}-pyversor-screenshot.png'.format(
                datetime.datetime.now().isoformat())
            screenshot = self.render()
            io.write_png(filename, screenshot)
            print('Saved screenshot with filename: {}'.format(filename))
        elif event.key.name == 'C':
            self.clear_view()
        elif event.key.name == 'F':
            # Toggle base frame
            if self._base_frame.parent is None:
                self._base_frame.parent = self.view.scene
            else:
                self._base_frame.parent = None

    def worker(self):
        global objects
        port = "5556"
        context = zmq.Context()
        socket = context.socket(zmq.PAIR)
        # socket.bind("tcp://127.0.0.1:%s" % port)
        socket.bind("tcp://*:%s" % port)

        while True:
            print("waiting")
            data = socket.recv()
            msg = pickle.loads(data)
            type_ = msg['type']
            if msg['clear']:
                clear_view()
            if type_ == 'sphere':
                draw_sphere(msg)
            elif type_ == 'path':
                print('got path')
                draw_path(msg)


if __name__ == '__main__':
    canvas = Gui()

    app.run()
