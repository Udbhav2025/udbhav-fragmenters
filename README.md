[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/wLMKZac9)  

# The Fragment Puzzler: Reassembling Cloud Data Shards (Image)                                           
## Mission:              
Cloud storage breaks files into tiny 'shards' for efficiency. This system analyzes thousands of mixed-up data fragments and figures out which piece fits where, like a digital jigsaw puzzle.                      
## MVP Requirements:              
  * Fragment Analysis: Recognize distinct visual edges on each data block
  * Automated Solver: Algorithm that matches edges like puzzle solver
  * Visual verification: Rebuild image to prove data integrity restored
## *Our Approach:*     
The images uploaded on cloud are stored in the form of _shards_. The core idea is to treat each image as a collection of smaller data chunks (or “fragments”) stored redundantly across the cloud. When an image needs to be accessed, the system scans the distributed storage network to locate its fragments based on the provided metadata. Using a combination of metadata analysis and C algorithms the system identifies which pieces belong together based on their compatibility and which versions are most complete or most recent.       




Our idea is to consider each individual shard and find its coners to form edge signatures of each of its sides. We use loops to compare the metadata(pixel count, SSD, number of bytes assigned, etc.) of the initial shard with the edge signatures of the other probable shards to find the one with most compatibility. We then concatenate the compatible fragments to the initial fragment and then iterate our way until we reach the last shard that we previously considered.                              
![The method in which we envision the fragments to form the image](https://img.freepik.com/free-vector/vector-grid-marking-user-hud-interface_1284-52212.jpg)




The ideal MVP then does a routine check to see whether each fragment is in the most optimal position for it, and if not, collects the unlikely fragments and rarranges them. To visualise the image, the fragments are rendered onto a canvas based on the final arrangement determined by the algorithms.








### Business Scope and Impact                                                                                                                                             
There are many images arcoss cloud which are blurred or have the files that are corrupted that causes them to lose their quality. Our MVP will be able to put together an end-to-end meaningful image from the isolated fragments with the usage of metadata. A meaningful image is one that posses clarity and achieving that would greatly improve the speed and efficiency of any field relying on a cloud to store data.

It can be applicable in the fields of Cyber Security, Satellite Image Processing, Data Recovery Labs, Government Law Enforcement and other such provisions to achieve more efficiency and have less room for errors. This will greatly impact out ability to extract information from images.
