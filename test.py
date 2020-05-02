#!/usr/bin/python

import os
import sys

tests = ['2+2', '2+2_var', 'if_else', 'interactive', 'println']

def java_file(test):
	return test_id + '.java'

def dot_file(test):
	return test_id + '.dot'

def png_file(test):
	return test_id + '.png'

output_dir = "TestOutput"

executable = './bin/MiniJavaCompiler'
parse_command = "{executable} ./java_examples/{test}.java --ast ./{dir}/{test}.dot"
render_image_command = "dot -Tpng ./{dir}/{test}.dot -o {dir}/{test}.png"

def parse_cmd(test):
	return parse_command.format(executable=executable, test=test, dir=output_dir)

def render_cmd(test, dir):
	return render_image_command.format(test=test, dir=dir)

def render(test, dir):
	print("[*] Rendering \'{}\'".format(test))
	stream = os.popen(render_cmd(test, dir))
	print(stream.read())

def run_single_test(test):
	print("[*] Running \'{}\' test".format(test))
	stream = os.popen(parse_cmd(test))
	print(stream.read())

def main(png_dir):
	for test in tests:
		run_single_test(test)

	for test in tests:
		render(test, png_dir)

def usage():
	print ("\tUsage: test.py\n")

if __name__ == "__main__":
	if len(sys.argv) > 1:
		path = sys.argv[1]
	else:
		path = output_dir
		
	main(path)
