files=dir('test_images');
filename={files.name};
path='test_images/';
for i=1:length(filename)
   system(['C:/Users/Rizard/Desktop/people_detection/people_detection/x64/Release/people_detection.exe ', path, filename{i}]); 
end