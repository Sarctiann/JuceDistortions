# JuceDistortions
This is my first project made eith JUCE framework.

---

This Repository contains a simple Distortion implemented on [JUCE Framework](https://github.com/juce-framework/JUCE) for the development of audio applications.

On the [`master`](https://github.com/Sarctiann/JuceDistortions/tree/master) branch I developed the ***ToyiDistortion*** (Toyi is my father, he is guitarrist).
![](https://github.com/Sarctiann/JuceDistortions/blob/master/Builds/Windows/screenshots/ToyiDistortion.png)

This are the maths behind: [Geogebra/ToyiDistortion](https://www.geogebra.org/m/kaccdhua)

---

On the [`ale`](https://github.com/Sarctiann/JuceDistortions/tree/ale) branch I developed the ***AM - 37*** it's a little variation of ToyiDistortion for my friend Alejandro Marasso.
![](https://github.com/Sarctiann/JuceDistortions/blob/master/Builds/Windows/screenshots/AleDistortion.png)

This are the maths behind: [Geogebra/AleDistortion](https://www.geogebra.org/m/mmkmswrn)

## Important:
I included the Juce headings just in case ... But these will not work for you because the routes of the Juce modules are in a different place in your system.
You must open RFDistortion.jucer with Projucer to setup the exporters and generate these files properly.

To work with this you should use other branch:
```
git checkout master # For ToyiDistortion
    # or
git checkout ale # For AleDistortion
```
once there, (on Linux) you can build the application:
```
cd Build/LinuxMakefile
make
```
To Run it:
```
./build/ToyiDistortion # For ToyiDistortion
    # or
./build/AleDistortion # For AleDistortion
    ```
