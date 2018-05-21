import os

filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
#filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt']
#filenames=['CR2_rebins.txt', 'CR2_xaxis.txt', 'CR2_yaxis.txt']

cust_rebin = 1
cust_xaxis_min = -999
cust_xaxis_max = 50

    #"m_Leadlfj_fjWclosest", "m_SubLeadlfj_fjWclosest", "m_llfj_fjWclosest",
    #//==== Onejet
    #"m_Leadlj", "m_SubLeadlj", "m_llj",

var_last = "HT"
NewVars = ["MT"]

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  for line in lines:

    tempfile.write(line)

    words = line.split()
    if words[1] == var_last:

      for NewVar in NewVars:
        newline = line.replace(var_last, NewVar)

        if "rebins" in filename:
          newline = words[0]+'\t'+NewVar+'\t10\n'
        if "xaxis" in filename:
          newline = words[0]+'\t'+NewVar+'\t0\t500\n'
        if "yaxis" in filename:
          newline = words[0]+'\t'+NewVar+'\t1000\n'

        tempfile.write(newline)

    #tempfile.write(line)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
