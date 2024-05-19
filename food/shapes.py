from PyShapes import *

shapes = PyShape("C:\\Users\\dorin\\Pictures\\food12.jpg")
shapes_dictionary = shapes.get_all_shapes()
shapes.show_shapes()
print(shapes_dictionary)
shapes.close()