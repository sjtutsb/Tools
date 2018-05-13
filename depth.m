clc; clear all;
x=[92.64,91.82,85.51,82.82;93.72,92.69,86.32,83.59;91.57,90.17,82.29,79.48;0,0,0,0]
b=bar(x)
ch=get(b,'children');
set(gca,'XTickLabel',{'55','65','75','85',''})
% set(gca,'XTickLabel',{'upload image','download image','download pdf','upload pdf'})
legend('SVD','VTM','CNNs','SSAE')
% xlabel('groups')
xlabel('dataset')
ylabel('Accuracy(%)')
% set(ylabel,'time(sec)',0:10:100)
set(gca,'yGrid','on')
