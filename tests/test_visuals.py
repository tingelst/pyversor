import sys
sys.path.append('build')

import numpy as np
import numpy.random as rnd


from pyversor_ import ega, cga
from pyversor_.cga.round import null, radius


from vispy import io
from vispy import scene
from vispy.gloo.util import _screenshot as screenshot
from vispy.visuals.transforms import MatrixTransform


canvas = scene.SceneCanvas(keys='interactive', bgcolor='white',
                           size=(800, 600), show=True)

view = canvas.central_widget.add_view()
view.camera = 'arcball'

a = cga.Vector(*rnd.randn(5))
b = cga.Vector(*rnd.randn(5))
c = cga.Vector(*rnd.randn(5))


m = cga.generate.exp(cga.DualLine(*rnd.randn(6)))
print(a)
print(a.spin(m))


print(cga.construct.meet(a,b))

m = MatrixTransform()
m.rotate(90, [1,0,0])
m.translate([1,2,3])

sphere1 = scene.visuals.Sphere(radius=radius(a), method='latitude', parent=view.scene,
                               edge_color='black')

sphere2 = scene.visuals.Sphere(radius=radius(b), method='ico', parent=view.scene,
                               edge_color='black')

sphere3 = scene.visuals.Sphere(radius=radius(c), rows=10, cols=10, depth=10,
                               method='cube', parent=view.scene,
                               edge_color='black')

base = scene.visuals.XYZAxis(parent=view.scene, antialias=True)
frame = scene.visuals.XYZAxis(parent=view.scene, antialias=True)
frame.transform = m

# sphere1.transform = STTransform(translate=[-2.5, 0, 0])
# sphere3.transform = STTransform(translate=[2.5, 0, 0])

# view.camera.set_range(x=[-3, 3])

# im = screenshot((0,0,canvas.size[0], canvas.size[1]))
# im = np.array(im)

# Add some text instructions
text = scene.visuals.Text("Drag right mouse button to zoom.", 
                          color='b',
                          anchor_x='left',
                          parent=view,
                          pos=(20, 30))
# # im[:, :, 3] = 255
# print(im)
# # io.write_png('frames.png', im)

if __name__ == '__main__' and sys.flags.interactive == 0:
    canvas.app.run()
