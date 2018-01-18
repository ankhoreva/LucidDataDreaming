# Lucid Data Dreaming

[Lucid Data Dreaming for Multiple Object Tracking](https://arxiv.org/abs/1703.09554), A. Khoreva, R. Benenson, E. Ilg, T. Brox and B. Schiele, arXiv preprint arXiv:1703.09554, 2017.


![TEASER](http://datasets.d2.mpi-inf.mpg.de/khoreva_LucidTracker/fig_arch.v2.png)


Lucid Data Dreaming is a data augmentation technique for semi-supervised video object segmentation (pixel-level object tracking).
It generates in-domain training data using the provided annotation on the first frame of each video to synthesize (“lucid dream”) plausible future video frames. This data augmentation allows us to train high quality appearance- and motion-based models for pixel-level tracking while using 20×∼100× less annotated data than competing methods.

Check our visit our [project page](https://www.mpi-inf.mpg.de/departments/computer-vision-and-multimodal-computing/research/weakly-supervised-learning/lucid-data-dreaming-for-object-tracking/) for pre-computed results on `DAVIS 2016`, `DAVIS 2017`, results visualization, and additional information.

## Usage
- To synthesize new images with lucid data dreaming, see `lucid_dream.m` 
- For demo about how to use this function, see `demo.m` 

## Contact

If you encounter any problems with the code, please contact [Anna Khoreva](https://www.mpi-inf.mpg.de/departments/computer-vision-and-multimodal-computing/people/anna-khoreva/) (khoreva at mpi-inf dot mpg dot de).

## Citation
If you use this code, please consider citing the following papers:

```
@inproceedings{LucidDataDreaming_arXiv17,
 title={Lucid Data Dreaming for Multiple Object Tracking},
 author={A. Khoreva and R. Benenson and E. Ilg and T. Brox and B. Schiele},
 booktitle={arXiv preprint arXiv: 1703.09554},
 year={2017}}

@inproceedings{LucidDataDreaming_CVPR17_workshops,
 title={Lucid Data Dreaming for Object Tracking},
 author={A. Khoreva and R. Benenson and E. Ilg and T. Brox and B. Schiele},
 booktitle={The 2017 DAVIS Challenge on Video Object Segmentation - CVPR Workshops},
 year={2017}}

```
