# Piano

**Alexa Berman, Collin Oalican, Riley Stutzman, and Sabian York** 

*(installations necessary to run the program)*
-*vcpkg*

## Summary of program:
- Our program is a virtual panio keyboard that is played by the keys on your laptop.
The white keys are played by the keys A, S, D, F, G, H, and J, while the black keys 
are played by the keys W, E, T, Y, and U. The keyboard displayed is only one octave 
(seven white keys and five black keys), however, the user can increase and decrease 
the octave by pressing the up or down key on their keyboard. Additionally, the different
keys light up different colors when they are played. 
- When the user presses the 0 key, the sound of the piano changes to a synthesizer sound.
The synthesizer sound wave is produced by a simple sine wave generator, and changes octave 
with the up and down keys as well. Also the keys light up the same colors as the piano keys 
when they are played.

### Future work:
- We could have made more user interface in the window, where the user could play the keys
by clicking on the piano keys on the window itself. Along the same lines, having visual button 
graphics that change both the ocatve and switch to synthesizer. 
- We could also implement an ADSR envelope and other synthesis techniques which we didn't have time for.

### Citations:
- In this project we used audio files for the piano keys:
https://pixabay.com/sound-effects/musical-all-88-piano-keys-sustain-48595/
- Additionally the color palette for the piano keys was generated from:
https://loading.io/color/feature/Rainbow/

### Grade breakdown/justification:
- Overall around 150 with additional bonus points
- 40pt : 'Main program complexity and usability'
- 20pt : 'Interactivity of program'
- 20pt : 'User exsperience'
- 20pt : 'Code organization'
- 0pt : 'Style and documentation' and 'video' and 'Lifespan'

Additionally in the project:

- We used OpenGL to render our keyboard in the window displayed.
- Also implemented, keyboard inputs that triggered both visual and sound effects.
- Exsplored the use of audio files and a simple sine wave generator to create the
sound of the piano and synthesizer respectively.