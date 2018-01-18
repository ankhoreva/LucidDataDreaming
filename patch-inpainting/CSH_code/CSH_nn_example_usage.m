% example usage for CSH_nn function
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all
clear all
clc

AddPaths

fprintf('CSH algorithm example script!!!\r\n');
fprintf('*******************************\r\n');


%% preparing the images
img1 = 'Saba1.bmp';
img2 = 'Saba2.bmp';

A = imread(img1);
B = imread(img2);

[hA wA dA] = size(A);
[hB wB dB] = size(B);

mpa = floor(hB*wB/1000) / 1000;
mpb = floor(hB*wB/1000) / 1000;

MP_A_Str = [num2str(mpa) ' MP'];
MP_B_Str = [num2str(mpb) ' MP'];

fprintf('Image A: %s, size = %s\r\n', img1 , MP_A_Str);
fprintf('Image B: %s, size = %s\r\n', img2 , MP_B_Str);


%% warmup
fprintf('Dummy run to warmup...');
CSH_ann = CSH_nn(A,B);
fprintf('Done!!\r\n');


%% Initialize random seed (this is useful mainly for debugging)
s = RandStream('swb2712','Seed',12345689);
RandStream.setDefaultStream(s)


%% Example 1: use internal defaults to show mapping
fprintf('1. Runing CSH_nn example with default parameter values\r\n');
CSH_TIC = tic;
%%%%%% CSH RUN %%%%%%%
CSH_ann = CSH_nn(A,B);
%%%%%%%%%%%%%%%%%%%%%%
CSH_TOC = toc(CSH_TIC);
fprintf('   CSH_nn elapsed time: %.3f[s]\r\n' , CSH_TOC);

width = 8; % Default patch width value
PlotExampleResults(A,B,CSH_ann,width,1,[],'default CSH');
    

%% Example 2: run CSH with user defined parameters settings
keyboard; close all

width = 4;
iterations = 4;
k = 1;
fprintf('2. Runing CSH_nn example: width = %d, iterations = %d, k = %d\r\n',width,iterations,k);
CSH_TIC = tic;
%%%%%% CSH RUN %%%%%%%
CSH_ann = CSH_nn(A,B,width,iterations,k,0);
%%%%%%%%%%%%%%%%%%%%%%
CSH_TOC = toc(CSH_TIC);
fprintf('   CSH_nn elapsed time: %.3f[s]\r\n' , CSH_TOC);
PlotExampleResults(A,B,CSH_ann,width,k,[],'CSH with parameters');


%% Example 3: run CSH for KNN mapping
keyboard; close all

width = 8;
iterations = 3;
k = 8;
fprintf('3. Runing CSH_nn example for KNN (K = %d) demonstration\r\n',k);
CSH_TIC = tic;
%%%%%% CSH RUN %%%%%%%
CSH_knn = CSH_nn(A,B,width,iterations,k,0);
%%%%%%%%%%%%%%%%%%%%%%
CSH_TOC = toc(CSH_TIC);
fprintf('   CSH_nn elapsed time: %.3f[s]\r\n' , CSH_TOC);
PlotExampleResults(A,B,CSH_knn,width,k,[],'CSH in KNN mode');


%% Example 4: run CSH ANN with mask
keyboard; close all

width = 8;
iterations = 3;
k = 1;
fprintf('4. Runing CSH_nn example with mask\r\n');

mask = zeros(hB,wB);
mask(round(hB/7):round(hB*6/7),round(wB/7):round(wB*6/7)) = 1; % Mark the patches that are NOT used for mapping

CSH_TIC = tic;
%%%%%% CSH RUN %%%%%%%
CSH_ann = CSH_nn(A,B,width,iterations,k,0,mask);
%%%%%%%%%%%%%%%%%%%%%%
CSH_TOC = toc(CSH_TIC);
fprintf('   CSH_nn elapsed time: %.3f[s]\r\n' , CSH_TOC);
PlotExampleResults(A,B,CSH_ann,width,k,mask,'CSH with masked area');


%% Example 5: run bidirectional CSH
% here we can see how to save time by running simultaneously in both directions
% in order to save in memory - we get a slightly worse B2A
keyboard; close all

width = 8;
iterations = 2;
k = 1;
fprintf('5. Runing CSH_nn example with bidirectional mapping\r\n');

close all
clc

% Initialize random seed (this is useful mainly for debugging)
s = RandStream('swb2712','Seed',123456789);
RandStream.setDefaultStream(s)

% and comparing to unidirectional:
tic
[CSH_ann_uni] = CSH_nn(A,B,width,iterations,k,0);
toc
tic
[CSH_bnn_uni] = CSH_nn(B,A,width,iterations,k,0);
toc

PlotExampleResults(A,B,CSH_ann_uni,width,k,[],'unidirectional CSH: A 2 B');
PlotExampleResults(B,A,CSH_bnn_uni,width,k,[],'unidirectional CSH: B 2 A');

% Initialize random seed (this is useful mainly for debugging)
s = RandStream('swb2712','Seed',123456789);
RandStream.setDefaultStream(s)

CSH_TIC = tic;
%%%%%% CSH RUN %%%%%%%
[CSH_ann,CSH_bnn] = CSH_nn(A,B,width,iterations,k,1);
%%%%%%%%%%%%%%%%%%%%%%
CSH_TOC = toc(CSH_TIC);
fprintf('   CSH_nn elapsed time: %.3f[s]\r\n' , CSH_TOC);


PlotExampleResults(A,B,CSH_ann,width,k,[],'bidirectional CSH: A 2 B');
PlotExampleResults(B,A,CSH_bnn,width,k,[],'bidirectional CSH: B 2 A');

% E O F
