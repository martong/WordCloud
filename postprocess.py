from optparse import OptionParser;

parser = OptionParser()
parser.add_option("-f", "--file", dest="file",
		help="read from FILE", metavar="FILE")
(options, args) = parser.parse_args()
optionsDict = options.__dict__
fname = optionsDict["file"]
with open(fname) as f:
	#content = f.readlines()
	for line in f:
		word = line.split(',')[0]
		count = line.split(',')[1]
		for x in range (0, int(count)):
			print word
