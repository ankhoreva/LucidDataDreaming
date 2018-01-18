function ann = AnnFromMatlab2c(bnn)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ann(:,:,1,:) = bnn(:,:,1,:) - 1;
ann(:,:,2,:) = bnn(:,:,2,:) - 1;
ann(:,:,3,:) = bnn(:,:,3,:);