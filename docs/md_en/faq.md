Frequently Asked Quetions
=========================

## Design Philosophy

OpenNovel consists of expertise of parallel processing and low power programming.

Our first motivation of the development of this software is a lack of OSS visual novel engines which run well on smartphones.
The development was not so easy but we achieved "runs well on smartphones". 

Smartphones have very low computer performances as they don't have cooling fans.
They have about 1/100 performance comparing to PC.
For example, assume that a rendering process can be done by a PC CPU with no problem.
That process may be done by a smartphone CPU in a short period,
but a few seconds later, it will be not properly done due to thermal throttling.
Such performance problem can be solved by a usage of GPU.
On the other hand, GPU proformances very differ on Android and iPhone.

Our method is a hybrid of CPU and GPU.
It renders the first and the last frames of a cross-fading by CPU, and interpolates them by GPU.
It utilizes CPU in a short period, and utilizes GPU with very low workload.

## Comparison With Other Game Engines

### What are the features of OpenNovel?

* OpenNovel is one of the leading novel engines for iOS and Android;
    * On smartphones, OpenNovel does not employ Unity or other third-party engines;
    * OpenNovel provides a Unity version to enable home game console porting.

### Is it possible to switch to OpenNovel from other engines?

* Switching works best if one plans to make creations for iOS and Android only.

### Where can works made with OpenNovel be published?

<ul>
  <li>Windows / Web browsers
  <ul>
    <li>For beginners, OpenNovel recommends “<a href="https://freem.ne.jp/change_language/change/en" target="_blank">Freem!</a>”;</li>
    <li>For advanced users, OpenNovel recommends publishing on “<a href="https://store.steampowered.com" target="_blank">Steam</a>” (Windows) and “<a href="https://itch.io" target="_blank">itch.io</a>” (Web browsers);</li>
    <li>If a submitted project does not break any website rules, it should be eagerly accepted there.</li>
  </ul>
  </li>
  <li>iPhone / iPad / Vision Pro
    <ul>
      <li>1. One may install an app on an Apple ID device (through Apple Development);</li>
      <li>2. If a device ID is registered in advance, one may install an app with AirDrop for up to 100 devices (through Ad Hoc);</li>
      <li>3. App Store publishing requires a comprehensive review of app contents by Apple (through App Store Connect).</li>
    </ul>
  </li>
  <li>Android
    <ul>
      <li>An APK file may be uploaded to a suitable location (such as Google Drive) as an independent app;</li>
      <li>It takes confirmations of many app testers to release one’s app on Google Play Store.</li>
    </ul>
  </li>
  <li>Home game consoles
    <ul>
      <li>Register as a developer on game console websites and submit your work;</li>
      <li>When filling out an application, specify “Unity” in the required “Middleware” and “Game Engine” fields;
</li>
      <li>Obtain a Unity release made for game consoles.</li>
    </ul>
  </li>
</ul>

### Can features of other engines be implemented in OpenNovel?
<p>
  That depends: For example, PCs are usually a hundred times more powerful than smartphones, thus, certain features must not be implemented in consideration of software porting.
</p>

## Creating Works With OpenNovel

### Can multiple characters be displayed on a screen?
<ul>
  <li>That can be achieved through OpenNovel rendering system called <a href="ciel.html">Ciel</a> (similar to YU-RIS/ERIS engine);</li>
  <li>For those who find Ciel too complicated, <a href="reference.html#chch"><code>@chch</code></a>  command should be used instead.</li>
</ul>

### Can a message box stay displayed while a character is changed?
<p>
  Change =0 to =1 in the project.txt file (as in the following example): 
</p>
<pre><code>msgbox.show.on.ch=1</code></pre>

### Can a character’s face be displayed next to a message box?
<p>
  An image of a character can be displayed at a special position via <code>face</code> instruction. Note that fade-in&nbsp;/&nbsp;fade-out time specifications are ignored for such images.
</p>
<pre><code>@ch face filename.png</code></pre>

### Can facial expression changes be done using only face parts?
<ul>
  <li>For smartphones, such changes&nbsp;— considering loading time, memory use, and composing time&nbsp;— may be impracticable, therefore, these features have not been implemented.</li>
</ul>

### Resolving font change issues:
<ul>
  <li>A font file name is recorded in the saved data, which may cause problems (such as not being able to change the font, or being told that a font file&nbsp;— that should not have been specified&nbsp;— cannot be opened).</li>
  <li>This issue can be solved by closing the program, deleting “<code>save</code>” folder (saved data), and restarting the program.  </li>
</ul>

### What are the steps to create a title screen?
<p>
  Please refer to “<a href="menu.html">How to Make a Menu Screen</a>” for the instructions.
</p>

### What are the options for a protagonist’s name?
<p>
  One can enter up to twenty-six names (from “%a” to “%z”).
</p>

### How to generate blinking eyes effect?
<p>
  Please refer to “<a href="eye-blink.html">Eye Blink</a>.”
</p>

### How to produce lip synchronization?
<p>
  Please refer to “<a href="lip-sync.html">Lip Sync</a>.”
</p>

### How to display dates and correspondences?
<ul>
  <li>Please use text layer and <a href="reference.html#text"><code>@text</code></a>.</li>
</ul>

### How to apply a filter to the entire screen?
<ul>
  <li>Use the effect layer;</li>
  <li>Cheap Android smartphones incapable of good image rendering are not recommended;</li>
  <li>Try creating an image closest to the color filter applied.</li>
</ul>

### Does OpenNovel has a macro function?
<ul>
  <li>Yes, there is <a href="reference.html#gosub"><code>@gosub</code></a> command available.</li>
  <li>Apply <a href="reference.html#using"><code>using</code></a> instruction to place macros into an external file.</li>
</ul>

### Does OpenNovel support CG viewing mode?
<ul>
  <li>Yes, using <a href="reference.html#menu"><code>@menu</code></a> command.</li>
  <li>Specify in the button configuration&nbsp;— <code>type: gallery;</code> and variable (for example)&nbsp;— <code>var: $1;</code></li>
  <li>If variable is 0, the button is not displayed;</li>
  <li>If variable is not 0, the button is displayed.</li>
</ul>

### Can a branch chart be created?
<ul>
  <li>Yes, using <a href="reference.html#menu"><code>@menu</code></a> command.</li>
</ul>

### Can a full-screen project be produced?
<p>
  Yes.
</p>

### Is it possible to center a ruby?
<p>
  Yes, it can be manually adjusted using half-width spaces (in fact, that is how professional developers do it). 
</p>

### Does OpenNovel support multiple languages?
<p>
  Yes, please refer to “<a href="multilingual.html">Multilingualization</a>.”
</p>

### Are there instructions on how to use plugin scripts?
<p>
  Yes, please refer to “<a href="plugin.html">Plugin Script</a>.”
</p>

### What bit rate should be used for audio files?
<ul>
  <li>For PCs:
    <ul>
      <li>BGM&nbsp;— Stereo 128&nbsp;Kbps;</li>
      <li>SE&nbsp;— Stereo 128&nbsp;Kbps;</li>
      <li>Voice&nbsp;— Mono 64&nbsp;Kbps;</li>
    </ul>
  </li>
  <li>For smartphones:
    <ul>
      <li>All Mono&nbsp;— 48&nbsp;Kbps;</li>
      <li>Mono because there is usually only one speaker;</li>
      <li>Stereo quality is inconsiderable for small speakers of smartphones, therefore, low bit rates are recommended to reduce one’s distribution size;</li>
      <li>However, if earphones are to be used, the same settings as for PCs may be recommended so that one’s playback is unaffected. </li>
    </ul>
  </li>
</ul>

### How to manage flags properly?
<ul>
  <li>Please name flags in your configuration file and comment on their purpose;</li>
  <li>Over time, good project maintenance depends on that;</li>
  <li>Comments should be phrased in such a way that they can be easily read and understood even a year later.</li>
</ul>
