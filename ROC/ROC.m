clear all;  
predict=(0:1/100:1);            %���ɼ��Ϊ0.01��Ԥ����ֵ  
ground_truth=randi([0,1],1,101);%����0-1�������  
result=plot_roc(predict,ground_truth);  
disp(result);
