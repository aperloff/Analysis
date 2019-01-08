import argparse
from DefaultOrderedDict import *

class RA2BinSelector():

	__var_title_dict = {"NJets":"N_{jet}",
						"BTags":"N_{b-jet}",
						"MHT":"H_{T}^{miss} [GeV]",
						"HT":"H_{T} [GeV]"}

	def __init__(self, argparse_arguments):
		self.args = argparse_arguments
		self.RA2VarNames = []
		self.all_bins = []
		self.RA2bins = []
		self.RA2binVec = []
		self.IDtoBinNumber = DefaultOrderedDict(list)
		self.RA2VarMin = []
		self.RA2VarMax = []
		self.ParseInputFile()

	#recursive function to implement variable # of for loops
	#ref: http://stackoverflow.com/questions/9555864/variable-nested-for-loops
	def FindBin(self, indices, bins, pos, bin_num, found_bins, found_bin_nums):
		for indices[pos] in range(0,len(bins[pos])):
			bin_num[pos] = bins[pos][indices[pos]]
			if pos == len(indices)-1:
				bin_number = self.IDtoBinNumber.get(tuple(bin_num))
				if bin_number != None:
					#print "pos:",pos
					#print "bin_number:",bin_number
					#print "bin_num:",bin_num
					found_bins.append(bin_number)
					found_bin_nums.append(list(bin_num))
			else:
				self.FindBin(indices,bins,pos+1,bin_num,found_bins,found_bin_nums)
		#print "pos:",pos
		#print "found_bins:",found_bins
		#print "found_bin_nums:",found_bin_nums

	def Get(self, varname):
		with open(self.args.infile,'r') as f:
			for line in f:
				line = line.rstrip()
				vtype, line = line.split(':')
				name, line = line.split('[')
				if varname not in name:
					continue
				line = line.replace(']','')
				vals = line.split(',')
				if vtype=="vfloat":
					vals = [float(i) for i in vals]
				elif vtype=="vstring":
					vals = [str(i) for i in vals]
				elif vtype=="vuint":
					vals = [int(i) for i in vals]
				else:
					raise TypeError("Unknown configuration type %s." % vtype)
				f.close()
				return vtype, name, vals

	def GetBin(self, qty_name, bin_num):
		for ivar,name in enumerate(self.RA2VarNames):
			if name==qty_name:
				return bin_num[ivar]
		return -1

	def GetBinNumbers(self):
		bins = []
		for ivar,name in enumerate(self.RA2VarNames):
			bins.append(self.GetBins(ivar))
			#skip loop if no bin was found for a value
			if len(bins[-1])==0:
				return [],[]
		#print "bins:",bins

		#set up for variable # of for loops
		indices = [0]*len(self.RA2VarNames)
		bin_num = [0]*len(self.RA2VarNames)
		found_bins = []
		found_bin_nums = []
		self.FindBin(indices,bins,0,bin_num,found_bins,found_bin_nums)
		bin_vec = found_bin_nums
		return found_bins, bin_vec

	def GetBins(self, qty):

		#load in some default values like the looper from KCode
		val = []
		if qty == 0: val.append(2.)
		elif qty == 1: val.append(0.)
		elif qty == 2: val.append(305.)
		elif qty == 3: val.append(305.)

		bins = []
		for iv, v in enumerate(val):
			for n in range(0,len(self.RA2VarMin[qty])):
				#print "iv="+str(iv)+" n="+str(n)+" val[iv]="+str(val[iv])+" "+str(self.RA2VarMin[qty][n])+" "+str(self.RA2VarMax[qty][n])
				if val[iv] > self.RA2VarMin[qty][n] and val[iv] <= self.RA2VarMax[qty][n]:
					bins.append(n)
		return bins

	def GetIntersection(self,line1par,line2par):
		# line1: y = m_1*x + b_1
		# line2: y = m_2*x + b_2
		# x_intersection = (b2 - b1) / (m1 - m2)
		# y_intersection = (m1*b2 - m2*b1) / (m1-m2)
		m1 = line1par[0]
		b1 = line1par[1]
		m2 = line2par[0]
		b2 = line2par[1]
		x_intersection = (b2 - b1) / (m1 - m2)
		y_intersection = ((m1*b2) - (m2*b1)) / (m1 - m2)
		return (x_intersection, y_intersection)

	def MakeBox(self,bounds,text,fill_style=0):
		box = TPaveText(bounds[0],bounds[1],bounds[2],bounds[3],"NB")
		box.SetLineWidth(1)
		box.SetLineColor(kBlack)
		box.SetLineStyle(kSolid)
		box.SetFillStyle(fill_style)
		if fill_style==1001:
			box.SetFillColor(kWhite)
		box.AddText(text)
		box.SetTextFont(62)
		box.SetTextSize(0.05)
		return box

	def MakeHashedBox(self,bounds):
		hashed_area = TBox(bounds[0],bounds[1],bounds[2],bounds[3])
		hashed_area.SetFillStyle(3004)
		hashed_area.SetFillColor(kBlue-2)
		return hashed_area

	def MakePlane(self,xvar,yvar):
		xvar_index = self.RA2VarNames.index(xvar)
		yvar_index = self.RA2VarNames.index(yvar)
		is_htmht = xvar=="HT" and yvar=="MHT"

		control_offset = 50
		x_min = self.RA2VarMin[xvar_index][0]
		y_min = self.RA2VarMin[yvar_index][0]-control_offset if is_htmht else self.RA2VarMin[yvar_index][0]

		x_padding = (self.args.VarMax[xvar_index]-x_min)*0.1
		y_padding = (self.args.VarMax[yvar_index]-y_min)*0.1

		c1 = TCanvas("c1","c1",10,10,700,500)
		c1.Range(x_min-2*x_padding,y_min-2*y_padding,self.args.VarMax[xvar_index]+x_padding,self.args.VarMax[yvar_index]+y_padding)
	
		#Draw the axis boundaries
		boundary_hash = self.MakeBox((x_min,y_min,self.args.VarMax[xvar_index],self.args.VarMax[yvar_index]),"",3144)
		boundary_hash.Draw()
		boundary = self.MakeBox((x_min,y_min,self.args.VarMax[xvar_index],self.args.VarMax[yvar_index]),"")
		boundary.SetLineWidth(3)
		boundary.Draw()

		#Draw a box for each bin
		latex = TLatex()
		latex.SetTextAlign(22)
		boxes = {}
		fills = {}
		hashes = {}
		bins = zip(self.all_bins[xvar_index],self.all_bins[yvar_index])
		for b in bins:
			bounds = (self.RA2VarMin[xvar_index][b[0]],self.RA2VarMin[yvar_index][b[1]],
					  self.RA2VarMax[xvar_index][b[0]] if self.RA2VarMax[xvar_index][b[0]] not in [99,9999] else self.args.VarMax[xvar_index],
					  self.RA2VarMax[yvar_index][b[1]] if self.RA2VarMax[yvar_index][b[1]] not in [99,9999] else self.args.VarMax[yvar_index])
			tpt = boxes.get(bounds)
			if tpt == None:
				fills[bounds] = self.MakeBox(bounds,"",1001)
				boxes[bounds] = self.MakeBox(bounds,"%i"%(b[0]+1) if is_htmht else "%i"%(len(boxes)+1))
				#Make a hashed box if b[0] in [0,3]
				if b[0] in [0,3] and is_htmht:
					hashes[bounds] = self.MakeHashedBox(bounds)
			#Append another box for control region if y_min == global y_min
			if self.RA2VarMin[yvar_index][b[1]] == y_min+control_offset and is_htmht:
				bounds = (self.RA2VarMin[xvar_index][b[0]],self.RA2VarMin[yvar_index][b[1]]-control_offset,
						  self.RA2VarMax[xvar_index][b[0]] if self.RA2VarMax[xvar_index][b[0]] not in [99,9999] else self.args.VarMax[xvar_index],
						  self.RA2VarMin[yvar_index][b[1]])
				tpt = boxes.get(bounds)
				if tpt == None:
					fills[bounds] = self.MakeBox(bounds,"",1001)
					boxes[bounds] = self.MakeBox(bounds,"C%i"%(b[0]+1))
					#Make a hashed box if b[0] in [0,3]
					if b[0] in [0,3] and is_htmht:
						hashes[bounds] = self.MakeHashedBox(bounds)
			#Draw axis labels
			if xvar in ["HT","MHT"]:
				if b[0]!=3 or xvar!="HT":
					latex.DrawLatex(self.RA2VarMin[xvar_index][b[0]],y_min-0.5*y_padding,"%i"%(self.RA2VarMin[xvar_index][b[0]]))
			else:
				x_center = 0.5*(boxes[bounds].GetX2()+boxes[bounds].GetX1())
				if self.RA2VarMax[xvar_index][b[0]] == self.RA2VarMin[xvar_index][b[0]] + 1:
					text = "%i"%(self.RA2VarMin[xvar_index][b[0]] + 1)
				elif self.RA2VarMax[xvar_index][b[0]] in [99,9999]:
					text = "#geq%i"%(self.RA2VarMin[xvar_index][b[0]] + 1)
				else:
					text = "%i-%i"%(self.RA2VarMin[xvar_index][b[0]] + 1,self.RA2VarMax[xvar_index][b[0]])
				latex.DrawLatex(x_center,y_min-0.5*y_padding,text)
			if yvar in ["HT","MHT"]:
				latex.DrawLatex(x_min-0.5*x_padding,self.RA2VarMin[yvar_index][b[1]],"%i"%(self.RA2VarMin[yvar_index][b[1]]))
			else:
				y_center = 0.5*(boxes[bounds].GetY2()+boxes[bounds].GetY1())
				if self.RA2VarMax[yvar_index][b[1]] == self.RA2VarMin[yvar_index][b[1]] + 1:
					text = "%i"%(self.RA2VarMin[yvar_index][b[1]] + 1)
				elif self.RA2VarMax[yvar_index][b[1]] in [99,9999]:
					text = "#geq%i"%(self.RA2VarMin[yvar_index][b[1]] + 1)
				else:
					text = "%i-%i"%(self.RA2VarMin[yvar_index][b[1]] + 1,self.RA2VarMax[yvar_index][b[1]])
				latex.DrawLatex(x_min-0.5*x_padding,y_center,text)

		#Draw the actual boxes
		for key,value in fills.iteritems():
			value.Draw()
		if is_htmht:
			for key,value in hashes.iteritems():
				value.Draw()
		for key,value in boxes.iteritems():
			value.Draw()

		#Draw the cutline if slope and y-intercept are set
		if args.cutline != None:
			lines = []
			for iline, line in enumerate(args.cutline):
				if line[0]!=xvar or line[1]!=yvar: continue

				#Calcualte the x value at which the line crosses the ymax. If it crosses that point before xmax, then reset the range
				# In other words, calculate the crossing point of the cutline and y=ymax
				point_intersection = self.GetIntersection((line[2],line[3]),(0,self.args.VarMax[yvar_index]))
				if point_intersection[0]<self.args.VarMax[xvar_index]:
					lines.append(TF1("func%i"%iline,"(%f*x)+%f"%(line[2],line[3]),x_min,point_intersection[0]))
				else:
					lines.append(TF1("func%i"%iline,"(%f*x)+%f"%(line[2],line[3]),x_min,self.args.VarMax[xvar_index]))
				lines[-1].SetLineWidth(2)
				lines[-1].SetLineStyle(kDashed)
				lines[-1].SetLineColor(kRed)
				lines[-1].Draw("same")

		#Re-Draw boundary so hashes don't overlap
		boundary.Draw()

		#Draw the axis labels
		latex.SetTextAlign(32)
		latex.DrawLatex(self.args.VarMax[xvar_index],y_min-1.5*y_padding,self.__var_title_dict.get(xvar))
		latex.SetTextAngle(90)
		latex.DrawLatex(x_min-1.5*x_padding,self.args.VarMax[yvar_index],self.__var_title_dict.get(yvar))
		c1.Print("%s_%s_%s"%(xvar,yvar,self.args.suffix))

	def ParseInputFile(self):
		#assemble vars from user input
		vtype, name, self.RA2VarNames = self.Get("RA2VarNames")
		if "HT" not in self.RA2VarNames or "MHT" not in self.RA2VarNames:
			if self.args.debug:
				print "type found:", vtype
				print "name found:", name
				print "RA2VarNames:", self.RA2VarNames
			raise RuntimeError("Either the HT or MHT variable is not present in the configuration file.")

		for ivar,name in enumerate(self.RA2VarNames):
			mintype, minname, min = self.Get("RA2Var%iMin"%ivar)
			maxtype, maxname, max = self.Get("RA2Var%iMax"%ivar)
			if len(min)!=len(max):
				raise ValueError("Input error: vector length mismatches in RA2Var%i min and max specification. RA2 binning will not be computed."%ivar)
			bintype, binname, bins = self.Get("RA2Var%iBins"%ivar)
			if ivar>0 and len(bins)!=len(self.all_bins[0]):
				raise ValueError("Input error: vector length mismatches in RA2Var%i bins specification. RA2 binning will not be computed."%ivar)

			#store vars
			self.RA2VarMin.append(min)
			self.RA2VarMax.append(max)
			self.all_bins.append(bins)

		#create map of RA2 bin IDs to bin numbers
		for ibin,bin in enumerate(self.all_bins[0]):
			bin_id = []
			for ivar,name in enumerate(self.RA2VarNames):
				bin_id.append(self.all_bins[ivar][ibin])
			self.IDtoBinNumber[tuple(bin_id)] = ibin+1 #bin numbers start at 1

def LinePar(s):
    try:
        var1, var2, m, b = s.split(',')
        return str(var1), str(var2), float(m), float(b)
    except:
    	print "s:",s
    	print "s.split(','):",s.split(',')
        raise argparse.ArgumentTypeError("Must specify the two variables being drawn (order matters), the slope, and the y-intercept of the line.")

if __name__ == "__main__":
	'''
	Examples of how to run:
	           2016: python BuildVarPlane.py -i input/input_RA2bin_options_original.txt -s plane_2016.pdf
	NJets3_MHT1_HT2: python BuildVarPlane.py -i input/input_RA2bin_options_Combination_NJet3_MHT1_HT2.txt -s plane_NJet3_MHT1_HT2.pdf -M 11 3 1100 2200
	NJets3_MHT1_HT3: python BuildVarPlane.py -i input/input_RA2bin_options_Combination_NJet3_MHT1_HT3.txt -s plane_proposed.pdf -c HT,MHT,1.0,0.0 -M 11 3 1100 2200

	VarMax by configuration:
	           2016: 10 3 1000 2100
	NJets3_MHT1_HT2: 11 3 1100 2200
	NJets3_MHT1_HT3: 11 3 1100 2200
	'''

	# Read parameters
	parser = argparse.ArgumentParser(description='Draw the bin variable planes.')
	parser.add_argument("-c", "--cutline",        type=LinePar, nargs='+',                       help="Add a line showing a cut along the plane with slope and y-intercept (default = %(default)s)")
	parser.add_argument("-d", "--debug",          action='store_true',                           help="Print extra debugging options (default = %(default)s)")
	parser.add_argument("-i", "--infile",         default='input/input_RA2bin_options.txt',      help="File containing the input bin mapping (default = %(default)s)")
	parser.add_argument("-M", "--VarMax",         default=[10,3,1000,2100], type=int, nargs='+', help="Maximum values for drawing purposes (default = %(default)s)")
	parser.add_argument("-s", "--suffix",         default="plane.pdf",                           help="Output filename suffix (default = %(default)s)")

	args, unknown = parser.parse_known_args()

	from ROOT import *

	myclass = RA2BinSelector(args)
	myclass.MakePlane("HT","MHT")
	myclass.MakePlane("NJets","BTags")
