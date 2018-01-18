% Plot error image of mapping
function [errImg, CSH_MeansRMS] = PlotExampleResults(A,B,CSH_Mapping,width,K_of_KNN,bMask,experimentName,patch_mode,A_patch,B_patch,patch_params,interactive,...
                                                            compensateOrientations,winnerOrientations_A,winnerOrientations_B,A_patch_normal,B_patch_normal)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PlotExampleResults - Plot results from example run
% A and B are the input images
% CSH_Mapping is the nn mapping of the CSH run
% Width is the used patch width

descriptor_mode = 0;

% keyboard
if (exist('patch_mode','var') && patch_mode)

    hA = patch_params.hA;
    wA = patch_params.wA;
    dA = patch_params.dA;
    hB = patch_params.hB;
    wB = patch_params.wB;
    dB = patch_params.dB;

    CSH_MeansRMS = 0;
    errImg = zeros(hA,wA);
    
    for t = 1:K_of_KNN
        [errImg_tmp,CSH_MeansRMS_tmp] = ...
            GetErrorMeanAndImage(CSH_Mapping(:,:,:,t),hB,wB,hA,wA,width,A,B,width,descriptor_mode,...
                                            patch_mode,A_patch,B_patch,patch_params);% Mapping error calculation
        CSH_MeansRMS = CSH_MeansRMS + CSH_MeansRMS_tmp;
        errImg = errImg + errImg_tmp;
    end
    errImg = errImg./K_of_KNN;
    CSH_MeansRMS = CSH_MeansRMS / K_of_KNN;
    
    if (exist('interactive') && interactive)
        dA_patch = double(A_patch);
        dB_patch = double(B_patch);

        h1 = figure;
        subplot 231; imshow(A); title('image A - CLICK HERE!');
        subplot 232; imagesc(errImg); axis off; hold on; 
            title(['avg error: ' num2str(CSH_MeansRMS,'%.0f')]); axis equal; axis tight
        subplot 233; imshow(B); title('image B');
        colors = {'r','g','b','c','y','m'};
        colors = {'g'};

    if (exist('compensateOrientations') && compensateOrientations)

        padSize = ceil((sqrt(2)-1)*width/2);
        paddedRGB = padarray(B,[padSize,padSize],'symmetric');

        [h,w] = size(winnerOrientations_A);
        wM1 = width - 1;
        numPatches = h*w;
         h7 = figure;
         figure(h1);
    end

        while 1
            subplot 231;
            [x,y,b] = ginput(1);
            if (b==3)
                break
            end
            x = floor(x); y = floor(y); % x = 161; y = 82;
            rColor = colors{randi(length(colors),1)};
            hold off; imshow(A); hold on; % clean old stuff
            plot(x,y,['*' rColor]);
            xB = CSH_Mapping(y,x,1);
            yB = CSH_Mapping(y,x,2);
            subplot 233;
            hold off; imshow(B); hold on; % clean old stuff
            plot(xB,yB,['*' rColor]);
            indA = (y-1)*wA + x;
            indB = (yB-1)*wB + xB;
            patchA = reshape(dA_patch(:,indA),[width,width,dA]);
            patchB = reshape(dB_patch(:,indB),[width,width,dB]);
            for dim = 1 : dA
                patchA(:,:,dim) = patchA(:,:,dim)';
                patchB(:,:,dim) = patchB(:,:,dim)';
            end
            
            absdiffPatch = abs(patchA - patchB);
            ssd = norm(patchA(:)-patchB(:));

            subplot 234; imshow(uint8(patchA)); title('patch A');
            subplot 235; imshow(uint8(absdiffPatch)); title(['diff patch. Error is: ' num2str(ssd)]);
            subplot 236; imshow(uint8(patchB)); title('patch B');
            
  if (exist('compensateOrientations') && compensateOrientations)
                figure(h7);
                
        blockRGB = paddedRGB(yB:yB+wM1+2*padSize,xB:xB+wM1+2*padSize,:);
        angle = rad2deg(winnerOrientations_B(yB,xB) - winnerOrientations_A(y,x)); % imrotate works counter-clockwise (and our angles are clockwise) so we are good
        if (angle==0)
            rotBlock = blockRGB;
        else
            rotBlock = imrotate(blockRGB,double(angle),'bicubic','crop');
        end
        finalBlock = rotBlock(padSize+1:end-padSize,padSize+1:end-padSize,:);
%         patchesRGB(:,blockNum) = finalBlock(:);

                % the old patch
                A_patch_normal = double(A_patch_normal); B_patch_normal = double(B_patch_normal);
                
                patA = reshape(A_patch_normal(:,indA),[width,width,dA]);
                patB = reshape(B_patch_normal(:,indB),[width,width,dB]);
                for dim = 1 : dA
                    patA(:,:,dim) = patA(:,:,dim)';
                    patB(:,:,dim) = patB(:,:,dim)';
                end
                dist1 = norm(patA(:)-patB(:));
                diff1 = abs(patA-patB);
                subplot 231; imshow(uint8(patA)); title(['patch A normal ' num2str(rad2deg(winnerOrientations_A(y,x)))]);
                subplot 232; imshow(uint8(diff1)); title(['diff orient ' num2str(norm(double(diff1(:))))]);                                
                subplot 233; imshow(uint8(patB)); 
                title(['patch B normal ' num2str(rad2deg(winnerOrientations_B(yB,xB))) ' dist: ' num2str(dist1)]);

                % the compensated one
                 for dim = 1 : dA
                    patchA(:,:,dim) = patchA(:,:,dim)';
                 end
                dist2 = norm(patchA(:)-patchB(:));
                diff2 = abs(patchA-patchB);
                subplot 234; imshow(uint8(patchA)); title(['patch A orient ' num2str(0)]);                                
                subplot 235; imshow(uint8(diff2)); title(['diff orient ' num2str(norm(double(diff2(:))))]);                                
                subplot 236; imshow(uint8(finalBlock)); 
                title(['patch B orient ' num2str(angle) ' dist: ' num2str(dist2)]);
                figure(h1);
            end
        end
    end
    
    return
end

[hA,wA,dA] = size(A);
[hB,wB,dB] = size(B);

CSH_MeansRMS = 0;
errImg = zeros(hA,wA);

for t = 1:K_of_KNN
    [errImg_tmp,CSH_MeansRMS_tmp] = ...
        GetErrorMeanAndImage(CSH_Mapping(:,:,:,t),hB,wB,hA,wA,width,A,B,width,descriptor_mode);% Mapping error calculation
    CSH_MeansRMS = CSH_MeansRMS + CSH_MeansRMS_tmp;
    errImg = errImg + errImg_tmp;
end

errImg = errImg./K_of_KNN;
CSH_MeansRMS = CSH_MeansRMS / K_of_KNN;

fprintf('    CSH_nn mapping RMS error: %.3f\r\n',CSH_MeansRMS);

if (exist('patch_mode','var') && patch_mode)
    return
end

figure;
if (exist('experimentName'))
    set(gcf,'name',experimentName)
end

br_boundary_to_ignore = width;
Hash_error_img = errImg(1:end - br_boundary_to_ignore,1:end - br_boundary_to_ignore);
pct98 = prctile(Hash_error_img(:),99);
Hash_error_img = min(pct98,errImg(1:end - br_boundary_to_ignore,1:end - br_boundary_to_ignore));
[I,J] = bounds(Hash_error_img(:),1);
[clims(1),clims(2)] = bounds([I,J],1);
clims(2) = max(clims(1) + 1, clims(2));
subplot(221);imshow(A); title('image A');
subplot(222);imshow(B); title('image B');
subplot(223);imagesc(Hash_error_img,clims); title(['CSH error: ' num2str(CSH_MeansRMS)]);


if (exist('bMask','var') && ~isempty(bMask))
    bMask(bMask>0)=512; % For representation only
    subplot(224);imagesc(bMask,clims); title('Binary mask (red = hole)');
end

% remove the boundaries
errImg = errImg(1:end - br_boundary_to_ignore,1:end - br_boundary_to_ignore);





