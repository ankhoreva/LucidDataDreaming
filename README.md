# Lucid Data Dreaming

#### A. Khoreva, R. Benenson, E. Ilg, T. Brox and B. Schiele 

[Lucid Data Dreaming for Multiple Object Tracking](https://arxiv.org/abs/1703.09554)


<div style="width:100%;text-align:center;">
<a href="url"><img src="http://datasets.d2.mpi-inf.mpg.de/khoreva_LucidTracker/fig_arch.v2.png" align="center" height="400"></a>
</div>

Convolutional networks reach top quality in pixel-level object tracking but require a large amount of training data (1k ∼10k) to deliver such results. We propose a new training strategy which achieves state-of-the-art results across three evaluation datasets while using 20×∼100× less annotated data than competing methods. Instead of using large training sets hoping to generalize across domains, we generate in-domain training data using the provided annotation on the first frame of each video to synthesize (“lucid dream”) plausible future video frames. In-domain per-video training data allows us to train high quality appearance- and motion-based models, as well as tune the post-processing stage. This approach allows to reach competitive results even when training from only a single annotated frame, without ImageNet pre-training. Our results indicate that using a larger training set is not automatically better, and that for the tracking task a smaller training set that is closer to the target domain is more effective. This changes the mindset regarding how many training samples and general “objectness” knowledge are required for the object tracking task.


## Contact

For any problem with implementation or bug, please contact [Anna Khoreva](https://www.mpi-inf.mpg.de/departments/computer-vision-and-multimodal-computing/people/anna-khoreva/) (khoreva at mpi-inf dot mpg dot de).

## Citation

Lucid Data Dreaming for Multiple Object Tracking, A. Khoreva, R. Benenson, E. Ilg, T. Brox and B. Schiele, arXiv preprint arXiv:1703.09554, 2017.
```
@inproceedings{LucidDataDreaming_arXiv17,
 title={Lucid Data Dreaming for Multiple Object Tracking},
 author={A. Khoreva and R. Benenson and E. Ilg and T. Brox and B. Schiele},
 booktitle={arXiv preprint arXiv: 1703.09554},
 year={2017}}

```
Lucid Data Dreaming for Object Tracking, A. Khoreva, R. Benenson, E. Ilg, T. Brox and B. Schiele. The 2017 DAVIS Challenge on Video Object Segmentation - CVPR Workshops, 2017.
```
@inproceedings{LucidDataDreaming_CVPR17_workshops,
 title={Lucid Data Dreaming for Object Tracking},
 author={A. Khoreva and R. Benenson and E. Ilg and T. Brox and B. Schiele},
 booktitle={The 2017 DAVIS Challenge on Video Object Segmentation - CVPR Workshops},
 year={2017}}

```
