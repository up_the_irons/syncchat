========================================
SyncChat BBS Telecommunications Software
========================================

:Author: Garry Dolley
:Date: 04-24-2021

Well, well, here we are...

After almost 25 years since I started to write the first version of SyncChat,
back in 1995, I'm releasing its code to the world in its entirety, at least from
what I could find in my archives.

The last working version was released around 1997, for DOS and OS/2 (I think),
and I think it was v2.7 or 2.8, or something like that.  I started to work on
the code again in 2004, probably trying to get it to compile on Linux, but I
don't recall what ultimately came of that effort.  That would have become v3.0,
and judging from the copyright banner in the current ``syncchat.c``, it was in
alpha state at the time.

Fast forward another decade or so, and I had started the open source process,
but I abandoned the task for one reason or another; I probably just got too busy
with `ARP Networks`_, traveling, or couldn't figure out how to get this thing to
compile again after another 10 years of it sitting in the dust.  Also, if I'm
being totally honest, the code is downright embarrassing.  I'm still surprised
to this day that it ran so well, and that there are still people who
occasionally email me for a registration code.  I wrote SyncChat during the
years when I was 15 to 17 years old, and at the time I thought I knew how to do
some decent C coding; but now, looking at how I had bastardized strings and the
lack of anything resembling responsible memory management, I'm reminded why I
didn't release this code sooner.

So, for better or for worse, here it is.  I don't remember how to compile
SyncChat in its current state.  There is a ``Makefile.gnu`` that I seem to
recall working, and I had it compiling on Linux, but I'm not sure if I ever got
it running within Synchronet, at the time.  Looking at a small script named
``publish.sh`` leads me to believe I indeed got the binary compiled.  In DOS, I
think it'll still compile with ``makefile.tcc``, as is, if you have Turbo C++
3.0, but obviously that is ancient and why would you even do that.

Another issue might be character encoding.  We used ANSI codes a lot back in the
DOS days.  They don't look right when I view the source code on my Arch Linux
laptop.  Might be a simple fix, or maybe not...

I'm happy to finally have this out there.  I've been encouraged to open source
this project for a long time and am glad I've at long last gone through with it.
Feel free to contact me and tell me about your BBS, life, compilation troubles
or if you want to chat over a beer 😆

.. _ARP Networks: https://arpnetworks.com

Author
------

Garry C. Dolley

gdolley [at] NO👀SPAM- arpnetworks.com

Social:

Instagram: `@up_the_irons <https://www.instagram.com/up_the_irons/>`_

YouTube: `Garry The Traveler <https://arp.serve.sh/youtube>`_

Formatting
----------

This README is formatted in reStructredText [RST]_.  It has the best
correlation between what a document looks like as plain text vs. its
formatted output (HTML, LaTeX, etc...).  What I like best is, markup
doesn't look like markup, even though it is.

.. [RST] http://docutils.sourceforge.net/rst.html

Copyright
---------

Copyright (c) 1995, 2021 Garry C. Dolley

Released under the MIT license.
