function [img_crop,y1,y2,x1,x2] = rotate_image(img, angle, interp)
    width = size(img,2); height = size(img, 1);
    img_rot = imrotate(img, angle, interp, 'loose');
    [wr, hr] = get_rectangle_with_max_area(width, height, pi*(angle/180));
    [img_crop,y1,y2,x1,x2] = crop_image_around_centre(img_rot, wr, hr);
    return
end
