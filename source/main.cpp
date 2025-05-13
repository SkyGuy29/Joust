/*
This is a replica of the 1982 arcade game Joust, programmed in sfml 2.6.2
in one semester by three seniors: two third years and one second year.

We hereby certify that this program represents our
work and that the design and logic were completed
without outside assistance.
*/

#include "Joust.h"
#include <Windows.h>


int main()
{
#ifdef NDEBUG
    FreeConsole();
#endif

    Joust joustGame;
    joustGame.run();
    return 0;

    /* Well. Here I am again at the end of another project. Quite literally, in fact. This is return 0, where the code ends when the
    user is done with it. The perfect place for the ending remarks. Everything returns, safe and secure. I did this at the end of Aero
    Fighters in second year, and I would like to do it again. A send-off message, hand typed, no AI.

	Thank you for being a part of this project. Thank you for all the fun moments and bugs that we laughed at. Thank you for sticking
    through the hard moments. Thank you for being flexible and for the ideas you pitched and created. We worked hard for an entire
    semester. Take a second to admire all that went into this. We did this. We wrote nearly every line you see here. The source files
    for this project wind up to be a total of 70 kilobytes of data. 70 thousand characters. Remember, every single one of those serves
    a purpose. That is what we did in a semester, 90 minutes once every other day. And would it not be fair to mention the research
    document and presentation? Every word, number, line, you name it had to be searched out. Dug for. Whether that was through the
    emulator or a video or a sketchy wiki page. There was not a light amount of effort that went into this project.	I know personally
    I like to have accomplishments that I worked hard towards. That is reflected in a lot of things I do and the choices I make. It
    gives me something to look back at, some evidence of abilities I have. This project fits right in there for all of us. This was
    big. This shows a lot of skills that you all have, from programming and problem-solving to teamwork and cooperation. All those
    things that employers love to see on resumes *cough*.

	Unlike the last time I did this, I will not refer to you by your real names here. I will just refer to you with the first letter
    of your names, and you can fill in the rest.

	R: Group projects are a much different beast than individual projects. In some ways it is easier and harder to work with groupmates.
    I get it. Keep in mind your own strengths and weaknesses and use them to your advantage. Maybe you feel like you didn't work that
    hard on this project, that you didn't contribute a lot. I would argue that that is not what really mattered here. You did work and
    you did help the group. Having you on the team made things better, regardless of how many lines you typed or how many classes you
    built. That's what matters, and by that metric you did a lot. And don't think this is meant to subtly say that you didn't contribute,
    that simply isn't true. Your research, your code, your ideas, they all made a significant impact on the project. Once again, things
    would look very different if you were not on the team.
    You were one of my biggest concerns on this project, but I don't mean that in a negative way. What I wanted, almost as much as a
    finished project, was to have you learn what we did last year. What a large group programming project looked like - both in terms
    of structure and tools. What it was like to work in a group on a project. What it was like to have meetings and deal with other
    people's work, for better or for worse. 
    I may have said this before, sorry if I sound like a broken record. I still think it is a great point to make. If I remember
    correctly, you were not continuing on going into CS. Great! I really do hope that you enjoy what you do next and that it works out
    well. I truly mean that. You are a good friend, keep it up. Sure, you most likely will not be programming. But you will be solving
    problems. A lot of the same problem-solving skills you learned through programming can be applied elsewhere. If you keep those in
    mind, you can accomplish a lot of really great things. And of course, you will encounter problems, that is part of the journey.
    Be ready for those to come up. Trust your gut, think through things, and the pieces will begin to fall into place.
    Thanks for your help this semester. Keep it up.

	P: I don't think I ever got the chance to tell you this. Jump start day just before freshman year I was really nervous about
    coming back to school. It was right after covid, I hadn't talked with anyone in the district for over a year. You were the first
    person from middle school that I recognized at Hickman as a former friend. Being able to reestablish that friendship helped me a
    lot that year, and I'm glad we've been able to keep it up since then. I can't say that about all the friends I made that year.
    Thank you for that. Don't say this one too loud, but you may have been the only other third year I would have been able to tolerate
    working with for this semester. I know at first you really wanted to work on Defender, but hopefully you had a good time with this
    project in its place. It meant a lot to me to be able to work with you this directly. You put in so much effort into this. It would
    not have been the same without you.
    I know as a third year working on basically the same thing you had been doing for literally the past year can definitely make you
    think that this probably didn't teach you anything. I don't think so. I believe that if you look for it, you can find something
    important from this project.
    I recall you saying that you did still want to pursue CS. Great! Hopefully your studies and classes go well. Use what you have
    learned from your three years well, both in your classes and beyond. I hope your future endeavors, projects, ideas, work, or
    whatever else you decide to spend your time on makes things worth it. 
    This section is definitely looking to be much shorter than the previous one. Sorry if I didn't have as much to say to you. Hopefully
    you can still find the meaning in these words. Thanks again for all you did this year. You're awesome.

	I'm seriously at a loss for words for what to put here to close this up. I don't know if I can share anymore gratitude without it
    sounding like everything else I've already stated, but I sure wish I could. I know I'm not the best at expressing how I feel with my
    body, so I hope these words better convey how I really feel.
    I can't say I will miss Joust. I can't say I will miss school. I'm excited to move on, to start another chapter. Maybe you feel the
    same way. Maybe you don't. Either way I hope some little bit of this project managed to improve your life in some way. Really,
    that's my only goal. That's why I do everything that I do. I just want to see people happy at the end of the day. Simple as that. 

    Thanks for improving my life. This meant the world to me.
	 -Sky. */
}

/*
easter eggs are illegal only ostrich eggs here
(paste as many inch cats as you want honestly idc)

nobody pasted any inch cats... oh well
*/