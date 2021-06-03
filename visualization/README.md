# pathos
Pathfinding experimentations to improve escape from dangerous areas

<div align = "center">
    <img src = "Bordeaux.png" width="720"/> 
</div>

## Escape visualization
Helps visualize evacuation plans and their behavior on a population of points. This should not be taken a measure of the efficiency of the algorithms, it is used to get an idea of their behavior.

## Showcase

Some pictures generated with `pathos` are available here: https://image.gabyfle.me

* Aquitaine: https://image.gabyfle.me/r/Aquitaine.png
* Bordeaux: https://image.gabyfle.me/v/Bordeaux.png
* New-York: https://image.gabyfle.me/v/New-York.png
* Île-de-France: https://image.gabyfle.me/r/Ile-de-France.png
* Paris: https://image.gabyfle.me/v/Paris.png

## Dependencies

* We're using [`pygame`](https://www.pygame.org) to render simulations.
* [`osmium`](https://osmcode.org/pyosmium/) is used to handle OpenStreetMap data files.
* [`numpy`](https://numpy.org/)is the library used to compute the mercator projection (absolute, sin, log)

## Using `pathos` to render areas
* Launch `pip install osmium numpy pygame`
* Download an OSM extract from a third-party website that allows you do to so
* Launch `start.py -i <downloaded_file> [-o render.png] [--ultra] [--ratio]`
    * Add `-o <filename.png>` to have a specific file name for the rendered image
    * Add `--ratio` to keep the same "width/height" ratio on the rendered image (warning, the produced image can be very large depending on the original parameters)
    * Add `--ultra` to render closed ways. This can be very heavy to render so you may expect some trouble while rendering large areas with this option

## License
Like this whole project, this is licensed under the Apache 2.0 license. See the corresponding "LICENSE" files to know the licenses of the different used libraries.
