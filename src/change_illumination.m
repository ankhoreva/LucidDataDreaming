function newRGB = change_illumination(RGB)
scale_power=[0.8:0.005:1.2];
add_value=[-0.05:0.001:0.05];
mult_value=[0.97:0.001:1.03];
HSV = rgb2hsv(RGB);
% Convert to HSV color space.
H=HSV(:,:,1);
S=HSV(:,:,2);
V=HSV(:,:,3);
% Alter S and V
S=mult_value(randsample(numel(mult_value),1))*S.^scale_power(randsample( numel(scale_power),1))+add_value(randsample(numel(add_value),1));
V=mult_value(randsample(numel(mult_value),1))*V.^scale_power(randsample( numel(scale_power),1))+add_value(randsample(numel(add_value),1));
% Reconstuct RGB image using altered Hue channel.
hsvImage = cat(3, H, S, V);
newRGB = hsv2rgb(hsvImage);
end

