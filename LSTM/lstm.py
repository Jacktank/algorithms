import sys
import codecs
sys.stdout = codecs.getwriter("utf-8")(sys.stdout.detach())

import tushare as ts
import numpy as np
import pandas as pd

#df = ts.get_k_data(code='600000', start='2015-10-01', end='2019-10-01')
#
#print(type(df))
#print(df.index)
#print(df.columns)
#print(df.head())
#

data_list = [112.,118.,132.,129.,121.,135.,148.,148.,136.,119.,104.,118.,115.,126.,141.,135.,125.,149.,170.,170.,158.,133.,114.,140.,145.,150.,178.,163.,172.,178.,199.,199.,184.,162.,146.,166.,171.,180.,193.,181.,183.,218.,230.,242.,209.,191.,172.,194.,196.,196.,236.,235.,229.,243.,264.,272.,237.,211.,180.,201.,204.,188.,235.,227.,234.,264.,302.,293.,259.,229.,203.,229.,242.,233.,267.,269.,270.,315.,364.,347.,312.,274.,237.,278.,284.,277.,317.,313.,318.,374.,413.,405.,355.,306.,271.,306.,315.,301.,356.,348.,355.,422.,465.,467.,404.,347.,305.,336.,340.,318.,362.,348.,363.,435.,491.,505.,404.,359.,310.,337.,360.,342.,406.,396.,420.,472.,548.,559.,463.,407.,362.,405.,417.,391.,419.,461.,472.,535.,622.,606.,508.,461.,390.,432.]

print(data_list)

length = 12
total_data = []
for i in range(len(data_list) - length):
    total_data.append((data_list[i:i+length], data_list[i+1:i+length+1]))

total_data = np.array(total_data, dtype=np.float32)
print(total_data.shape)
train_data = total_data[:-1]
test_data = total_data[-1:]

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.autograd import *

torch.manual_seed(1)

def ToVariable(x):
    tmp = torch.FloatTensor(x)
    return Variable(tmp)

class LSTMpred(nn.Module):
    def __init__(self, input_size, hidden_size, output_size=1, num_layers=2):
        super().__init__()
        
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size
        self.num_layers = num_layers

        self.lstm = nn.LSTM(input_size, hidden_size, num_layers)
        self.fc = nn.Linear(hidden_size, output_size)
        self.hidden_var = self.init_hidden()

    def init_hidden(self):
        # return (Variable(torch.zeros(self.num_layers, 1, self.hidden_size, dtype=torch.float32)),
        #         Variable(torch.zeros(self.num_layers, 1, self.hidden_size, dtype=torch.float32)))
         return (Variable(torch.zeros(self.num_layers, 1, self.hidden_size)),
                Variable(torch.zeros(self.num_layers, 1, self.hidden_size)))
    
    def forward(self, x_):
        if self.training:
            # print('train...')
            x, self.hidden_var = self.lstm(x_, self.hidden_var)
            s, b, h = x.shape
            assert b == 1
            x = x.view(s*b, -1)
            output = self.fc(x)
            output = output.view(s, b, -1)
            return output
        else:
            print('test...')
            x, self.hidden_var = self.lstm(x_, self.hidden_var)
            s, b, h = x.shape
            assert b == 1
            x = x.view(s*b, -1)
            output = self.fc(x)
            output = output.view(s, b, -1)
            return output


model = LSTMpred(1, 100)
loss_function = nn.MSELoss()
optimizer = optim.SGD(model.parameters(), lr=0.01)

model.train()
for epoch in range(10):
    print(epoch)
    i=0
    for seq, outs in train_data:
        seq = ToVariable(seq).view(-1, 1, 1)
        outs = ToVariable(outs).view(-1, 1, 1)
        print(i)
        # print(seq.shape)
        # print(outs.shape)

        optimizer.zero_grad()
        model.hidden_var = model.init_hidden()

        modout = model(seq)
        loss = loss_function(modout, outs)
        loss.backward()
        optimizer.step()
        i += 1

model.test()
for seq, outs in test_data:
        seq = ToVariable(seq).view(-1, 1, 1)
        outs = ToVariable(outs).view(-1, 1, 1)
        # print(seq.shape)
        # print(outs.shape)

        model.hidden_var = model.init_hidden()

        modout = model(seq)

        

# import torch
# import torch.nn as nn
# from torch.autograd import *
# import torch.optim as optim
# import torch.nn.functional as F
# import matplotlib.pyplot as plt
# import numpy as np
 
# def SeriesGen(N):
#     x = torch.arange(1,N,0.01)
#     return torch.sin(x)
 
# def trainDataGen(seq,k):
#     dat = list()
#     L = len(seq)
#     for i in range(L-k-1):
#         indat = seq[i:i+k]
#         outdat = seq[i+1:i+k+1]
#         dat.append((indat,outdat))
#     return dat
 
# def ToVariable(x):
#     tmp = torch.FloatTensor(x)
#     return Variable(tmp)
 
# y = SeriesGen(10)
# dat = trainDataGen(y.numpy(),10)
 
 
# class LSTMpred(nn.Module):
 
#     def __init__(self,input_size,hidden_dim):
#         super(LSTMpred,self).__init__()
#         self.input_dim = input_size
#         self.hidden_dim = hidden_dim
#         self.lstm = nn.LSTM(input_size,hidden_dim)
#         self.hidden2out = nn.Linear(hidden_dim,1)
#         self.hidden = self.init_hidden()
 
#     def init_hidden(self):
#         return (Variable(torch.zeros(1, 1, self.hidden_dim)),
#                 Variable(torch.zeros(1, 1, self.hidden_dim)))
 
#     def forward(self,seq):
#         lstm_out, self.hidden = self.lstm(
#             seq.view(len(seq), 1, -1), self.hidden)
#         outdat = self.hidden2out(lstm_out.view(len(seq),-1))
#         return outdat
 
 
# model = LSTMpred(1,6)
# loss_function = nn.MSELoss()
# optimizer = optim.SGD(model.parameters(), lr=0.01)
 
# for epoch in range(10):
#     print(epoch)
#     for seq, outs in dat[:700]:
#         seq = ToVariable(seq)
#         outs = ToVariable(outs)
#         #outs = torch.from_numpy(np.array([outs]))
 
#         optimizer.zero_grad()
 
#         model.hidden = model.init_hidden()
 
#         modout = model(seq)
 
#         loss = loss_function(modout, outs)
#         loss.backward()
#         optimizer.step()
 
# predDat = []
# for seq, trueVal in dat[700:]:
#     seq = ToVariable(seq)
#     trueVal = ToVariable(trueVal)
#     predDat.append(model(seq)[-1].data.numpy()[0])
 
 
# fig = plt.figure()
# plt.plot(y.numpy())
# plt.plot(range(700,890),predDat)
# plt.show()
