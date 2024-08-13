To run, you must choose the following parameters:
  Key Point detection method (-d). Available ones are:
    - fast
    - orb
    - brisk
    - sift
    - surf (default)

  Descriptor generation method (-g). Available ones are:
    - orb
    - brisk
    - sift
    - surf (default)

  Descriptor matching method (-m). Available ones are:
    - brute (brute force)
    - flann (default)

  Path to an image that contains the target object (-t).

Example:
  $ ./run -d fast -g surf -m flann -t target/image.png
