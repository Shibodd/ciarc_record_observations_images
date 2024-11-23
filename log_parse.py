import json
import base64
import io
import PIL.Image

def read_one_record(f) -> dict:
  return json.loads(f.readline())

def get_image(record) -> PIL.Image.Image:
  return PIL.Image.open(io.BytesIO(base64.b64decode(record['png_base64'])))

def get_observation(record) -> dict:
  return record['observation']