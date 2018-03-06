import os

lines = open('result.txt').readlines()

mZR = []
mN = []
Xsec = []

for line in lines:

  words = line.split()
  sample = words[0]
  xsec = words[1]

  ## ZRToNuNuToMuMuJJJJ_MWR-5000_MZR-1000_MHN-100_13TeV-pythia8	8.510e-01
  sample_words = sample.split('_')
  ## ['ZRToNuNuToMuMuJJJJ', 'MWR-5000', 'MZR-1000', 'MHN-100', '13TeV-pythia8']

  WR_mass = sample_words[1].replace('MWR-','')
  Zp_mass = sample_words[2].replace('MZR-','')
  HN_mass = sample_words[3].replace('MHN-','')
  #print WR_mass+'\t'+Zp_mass+'\t'+HN_mass+'\t'+xsec

  mZR.append(Zp_mass)
  mN.append(HN_mass)
  Xsec.append(xsec)

print 'vector<double> vec_mZR = {'
for a in mZR:
  print a+',',
print '\n};'

print 'vector<double> vec_mN = {'
for a in mN:
  print a+',',
print '\n};'

print 'vector<double> vec_Xsec = {'
for a in Xsec:
  print a+',',
print '\n};'
  
