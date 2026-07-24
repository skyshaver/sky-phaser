#https://markvtechblog.wordpress.com/2024/04/28/code-generation-in-python-with-jinja2/
import yaml
from jinja2 import Environment, FileSystemLoader

# assumes this file is in a dir at the same level as /source
path_to_json_serializercpp = "../source/JsonSerializer.cpp"

with open('parameters.yaml', 'r') as yaml_file:
    data = yaml.safe_load(yaml_file)

env = Environment(loader=FileSystemLoader('.'), trim_blocks=True, lstrip_blocks=True)
template = env.get_template('jsonSerializerCpp_tmpl.jinja2')

output = template.render(parameters=data['Parameters'])

with open(path_to_json_serializercpp, 'w') as cpp_file:
    cpp_file.write(output)