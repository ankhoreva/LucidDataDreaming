function [image,y1,y2,x1,x2] = crop_image_around_centre(image, width, height)
    % Given an image, crops it to the given width and height, around it's centre point
    image_size = [size(image, 2), size(image, 1)];
    image_center = [round(image_size(1) * 0.5), round(image_size(2) * 0.5)];
    
    if(width > image_size(1))
        width = image_size(1);
    end
    if(height > image_size(2))
        height = image_size(2);
    end
    
    x1 = round(image_center(1) - width * 0.5)+1;
    x2 = round(image_center(1) + width * 0.5);
    y1 = round(image_center(2) - height * 0.5)+1;
    y2 = round(image_center(2) + height * 0.5);
    
    image = image(y1:y2-1, x1:x2-1,:);
end


