class Cow:
	def __init__(self, name: str):
	#constructor for the class
		self.name = name

	def get_name(self):
	#return the cow's name
		return self.name

	def get_image(self):
	#return the cow's image
		return self.image

	def set_image(self, _image: str):
		self.image = _image