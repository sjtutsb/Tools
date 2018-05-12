% source video path 'C:\Users\tong\Documents\MATLAB\imagegait\video\video.avi'
% generate frames path 'C:\Users\tong\Documents\MATLAB\imagegait\video\video\00000*.jpg'
% mainpath='C:\Users\sibin\Documents\MATLAB\imagegait\';
files=dir(mainpath);  %%填写要存放序列图像的目录
for i=1:length(files)
    if  ~strcmp(files(i).name,'.') && ~strcmp(files(i).name,'..')
       videofiles=dir(strcat(mainpath,files(i).name));
        for j=1:length(videofiles)
            if strcmp(videofiles(j).name,'.') || strcmp(videofiles(j).name,'..')
                continue;
            end
           if ~isdir([mainpath files(i).name '\' videofiles(j).name(1:end-4)])
                mkdir([mainpath files(i).name '\' videofiles(j).name(1:end-4)]);
           end
            [mainpath files(i).name '\' videofiles(j).name]
            mov=VideoReader([mainpath files(i).name '\' videofiles(j).name]);
            fnum=mov.NumberOfFrame;
            for k=1:fnum
                image=read(mov,k);
                imwrite(image,[mainpath files(i).name '\' videofiles(j).name(1:end-4) '\' num2str(k,'%06d') '.jpg']);
            end
        end
    end
end