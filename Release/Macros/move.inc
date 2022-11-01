|
|   move.inc
|
|Advanced moving and object-avoidance routines
|
|Originally by beatnik007 (Who credits Mckorr)
|
|Revised and converted to MQ2Data by Terramantian
|
|Signifagant and on-going Improvments by EQBot_Man   8.9.04
|   Added /call MoveToSpawnName
|      This will take a partial name and a distance and reliably target and move
|      to the nearest spawn of that name
|   Added code to get you to stop a lot closer than 10 units.  You should stop almost
|      right at the location you want when using MoveToLoc
|   Sometimes you would get stuck at a door and if you were macroing unattended
|      you would continue to strafe for hours making it obvious you were
|      macroing.  Added code that if the strafe function is called more
|      than 10 times in 60 sec to /quit you out
|   Have added lots of little checks including NULL targets and corpse checks and a lot
|      of little things that I can't remember now but I needed to add due to rare
|      circumstances of the subroutines failing to do what they were desigend to do.
|
|  Subroutines:
|   Sub MoveToLoc
|      Moves you to a specified xy loc
|   Sub MoveToSpawn
|      Moved you to a specified ID number(pretty pointless)
|   Sub MoveToSpawnName
|      Moves you to the nearest spawn given a partial or full name
|
|===================================================|


| Sub MoveToLoc                                     |
|---------------------------------------------------|
|This simply moves the player to within 1 unit of |
|the requested location, while avoiding obstacles   |
|                                                   |
|This is beatnik007's original sub, with a few minor|
|changes and rewritten in MQ2Data format            |
|                                                   |
|SYNTAX: /call MoveToLoc Y X                        |


Sub MoveToLoc(MoveToY, MoveToX)
    /echo Moving to Location: ${MoveToY}, ${MoveToX}. HP = ${Me.PctHPs}
    /declare FailureTimer timer local 0
    /declare StrafeFailure int local
    /declare running int local
    /declare MaxSpeed int local
    /declare StopDistance int local
    /declare distanceNow float local
    /declare distanceBefore float local
    /declare distanceModifier int local
    /varset running 0
    /declare distanceTimer timer 15
    /varset distanceBefore ${Math.Distance[${Me.Y},${Me.X}:${MoveToY},${MoveToX}]}
    /varset distanceModifier 1
    /varset MaxSpeed 0
    :moveToLocation

   /if (${Me.Speed}>=${MaxSpeed}) /varset MaxSpeed ${Me.Speed}
   /if (${MaxSpeed}<=166) {
      /varset StopDistance 3
   } else {
      /varset StopDistance 10
   }

    /face fast nolook loc ${MoveToY},${MoveToX}

    /if (${Math.Distance[${Me.Y},${Me.X}:${MoveToY},${MoveToX}]}<${StopDistance}) {
        /keypress forward
        /return
    }

    /if (${distanceTimer}==0) {
        /if (${Me.Sneaking}) {
            /varset distanceModifier 2
        } else {
            /varset distanceModifier 1
       }
        /varset distanceNow ${Math.Distance[${Me.Y},${Me.X}:${MoveToY},${MoveToX}]}
        /if (${Math.Calc[${distanceBefore}-${distanceNow}]}<${Math.Calc[10/${distanceModifier}]}) {
           /if (${FailureTimer}==0) {
              /varset StrafeFailure 0
              /varset FailureTimer 600
           }
           /if (${FailureTimer}>0) {
              /varset StrafeFailure ${Math.Calc[${StrafeFailure} + 1]}
           }
      /if (${StrafeFailure}>=10 && ${FailureTimer}>0) {
             /keypress forward
             /keypress back hold
             /delay 5
                 /keypress back
         /afk Be back later, leave a message
         /echo Your movement failed more than 10 times in 30 seconds and most likely looked macroed.  Ending macro. . .
         /exit
         /endmacro
         /quit
      }
            /call strafePastObstacle ${StrafeFailure}
        }

        /varset distanceBefore ${Math.Distance[${Me.Y},${Me.X}:${MoveToY},${MoveToX}]}
        /varset distanceTimer 15
    }

    /if (${running}==0) {
        /keypress forward
        /if (${Math.Distance[${Me.Y},${Me.X}:${MoveToY},${MoveToX}]}>${StopDistance}) {
            /varset running 1
            /keypress forward hold
        }
    } else {
        /if (${Math.Distance[${Me.Y},${Me.X}:${MoveToY},${MoveToX}]}<${StopDistance}) {
            /varset running 0
            /keypress forward
        }
    }
    /goto :moveToLocation
/return


| Sub MoveToSpawn                                   |
|---------------------------------------------------|
|This moves the player to within a provided distance|
|of the provided spawn, while avoiding obstacles    |
|                                                   |
|I "wrote" this, but as you can see, it's the same  |
|as MoveToLoc with a few variable replacements.     |
|                                                   |
|The second parameter, Distance, allows for the     |
|player to stop short of the target by a certain    |
|amount, to provide for different aggro radii, etc. |
|                                                   |
|SYNTAX: /call MoveToSpawn ID Distance              |

Sub MoveToSpawn(MoveToID, StopDistance)


    /if (!(${Defined[MoveToID]})||(${Spawn[MoveToID].ID})) {
        /echo Spawn ID not found or no ID provided. Aborting...
        /return
    }
    /if (!(${Defined[StopDistance]})) {
        /declare StopDistance int local
        /varset StopDistance 10
    }
    /echo Moving to Spawn: ${MoveToID} (${Spawn[${MoveToID}].CleanName}).
    /echo Current Location: ${Spawn[${MoveToID}].Y}, ${Spawn[${MoveToID}].X}
    /echo Current Distance: ${Spawn[${MoveToID}].Distance}
    /declare FailureTimer timer local 0
    /declare StrafeFailure int local
    /declare running int local
    /declare distanceNow float local
    /declare distanceBefore float local
    /declare distanceModifier int local
    /varset running 0
    /declare distanceTimer timer 15
    /varset distanceBefore ${Spawn[${MoveToID}].Distance}
    /varset distanceModifier 1

    :moveToSpawn

    /squelch /face fast nolook id ${MoveToID}

    /if (${Spawn[${MoveToID}].Distance}<${StopDistance}) {
        /keypress forward
        /return
    }

    /if (${distanceTimer}==0) {
        /if (${Me.Sneaking}) {
            /varset distanceModifier 2
        } else {
            /varset distanceModifier 1
        }
        /varset distanceNow ${Spawn[${MoveToID}].Distance}
        /if (${Math.Calc[${distanceBefore}-${distanceNow}]}<${Math.Calc[10/${distanceModifier}]}) {
           /if (${FailureTimer}==0) {
                   /varset StrafeFailure 0
                   /varset FailureTimer 600
                }
                /if (${FailureTimer}>0) {
                   /varset StrafeFailure ${Math.Calc[${StrafeFailure} + 1]}
                }
           /if (${StrafeFailure}>=10 && ${FailureTimer}>0) {
                  /keypress forward
                  /keypress back hold
                  /delay 5
                      /keypress back
                      /sit
              /afk Be back later, leave a message
              /echo Your movement failed more than 10 times in 30 seconds and most likely looked macroed.  Ending macro. . .
              /exit
              /endmacro
         /quit
           }
            /call strafePastObstacle ${StrafeFailure}
        }
        /varset distanceBefore ${Spawn[${MoveToID}].Distance}
        /varset distanceTimer 15
    }

    /if (${running}==0) {
        /keypress forward
        /if (${Spawn[${MoveToID}].Distance}>=${StopDistance}) {
            /varset running 1
            /keypress forward hold
        }
    } else {
        /if (${Spawn[${MoveToID}].Distance}<${StopDistance}) {
            /varset running 0
            /keypress forward
        }
    }
    /goto :moveToSpawn
/return


| Sub MoveToSpawnName                               |
|---------------------------------------------------|
|This moves the player to within a provided distance|
|of the provided spawn, while avoiding obstacles    |
|                                                   |
|I "wrote" this, but as you can see, it's the same  |
|as MoveToLoc with a few variable replacements.     |
|                                                   |
|The second parameter, Distance, allows for the     |
|player to stop short of the target by a certain    |
|amount, to provide for different aggro radii, or to|
|attack.                                            |
|                      |
|SYNTAX: /call MoveToSpawnName Name Distance        |
|   Does take partial names:          |
|   /call MoveToSpawnName skel 9          |
|      to move you to the nearest skeleton |
|                      |
|  I use this for farming bone chips and silks       |

Sub MoveToSpawnName(Name, StopDistance)
/keypress esc
/target ${Name} npc
/delay 2
/if (${String[${Target}].Find["NULL"]}) /return
/if (${String[${Target}].Find["corpse"]}) /return
    /if (!${Target.ID}) {
        /echo Name not found or no name provided. Aborting...
        /return
    }
    /if (!(${Defined[StopDistance]})) {
        /declare StopDistance int local
        /varset StopDistance 70
    }
    /echo Moving to Spawn: ${Target.CleanName}.
    /declare FailureTimer timer local 0
    /declare StrafeFailure int local
    /declare running int local
    /declare distanceNow float local
    /declare distanceBefore float local
    /declare distanceModifier int local
    /varset running 0
    /declare distanceTimer timer 15
    /varset distanceBefore ${Target.Distance}
    /varset distanceModifier 1

    :moveToSpawn
   /if (${String[${Target}].Find["NULL"]}) /return
    /face fast predict

    /if (${Target.Distance}<${StopDistance}) {
        /keypress forward
        /return
    }

    /if (${distanceTimer}==0) {
        /if (${Me.Sneaking}) {
            /varset distanceModifier 2
        } else {
            /varset distanceModifier 1
        }

        /varset distanceNow ${Target.Distance}
        /if (${Math.Calc[${distanceBefore}-${distanceNow}]}<${Math.Calc[10/${distanceModifier}]}) {
           /if (${FailureTimer}==0) {
                   /varset StrafeFailure 0
                   /varset FailureTimer 600
                }
                /if (${FailureTimer}>0) {
                   /varset StrafeFailure ${Math.Calc[${StrafeFailure} + 1]}
                }
           /if (${StrafeFailure}>=10 && ${FailureTimer}>0) {
                  /keypress forward
                  /keypress back hold
                  /delay 5
                      /keypress back
                      /sit
              /afk Be back later, leave a message
              /echo Your movement failed more than 10 times in 30 seconds and most likely looked macroed.  Ending macro. . .
              /exit
              /endmacro
         /quit
           }
            /call strafePastObstacle ${StrafeFailure}
        }
        /varset distanceBefore ${Target.Distance}
        /varset distanceTimer 15
    }

    /if (${running}==0) {
        /keypress forward
        /if (${Target.Distance}>=${StopDistance}) {
            /varset running 1
            /keypress forward hold
        }
    } else {
        /if (${Target.Distance}<${StopDistance}) {
            /varset running 0
            /keypress forward
        }
    }
    /goto :moveToSpawn
/return

| Only to be used by the previous functions - It's obvious what it does. |

sub strafePastObstacle(Number)
    /keypress forward
    /keypress back hold
    /delay ${Math.Calc[${Number}*3/2+4]}
    /keypress back
    /if (!${Me.State.Equal["STAND"]}) /stand
    /if (${Math.Rand[99]}>50) {
        /keypress strafe_right hold
    } else {
        /keypress strafe_left hold
    }
    /delay ${Math.Calc[${Number}*4+5]}
    /keypress strafe_right
    /keypress strafe_left
    /keypress forward hold
/return

Sub Turn(THeadingY,THeadingX)
   /declare PHeading outer 0
   /declare THeading outer 0
   /declare Bearing outer 0
   /declare IsTurning outer 0
   /declare TurnKey outer NULL

:TurnLoop
   /delay 0
   /if (${Me.Sitting}) /sit off
   /varset PHeading ${Me.Heading.Degrees}
   /if (${Defined[THeadingX]}) {
      /varset THeading ${Heading[${THeadingY},${THeadingX}].Degrees}
   } else {
      /varset THeading ${Target.HeadingTo.Degrees}
   }

   /varset Bearing ${Math.Calc[(${PHeading}-${THeading}+540)%360-180]}

   /if (${Bearing}>=-7 && ${Bearing}<=7) {
      /if (${String[${TurnKey}].NotEqual[NULL]}) /keypress ${TurnKey}
      /face heading ${Heading[${THeading}].Degrees} nolook
      /return
   } else /if (${Bearing}>=-180 && ${Bearing}>=7) {
      /if (${String[${TurnKey}].NotEqual[LEFT]}) /varset TurnKey LEFT
   } else /if (${Bearing}<=180 && ${Bearing}<=7) {
      /if (${String[${TurnKey}].NotEqual[RIGHT]}) /varset TurnKey RIGHT
   }

   /if (!${IsTurning}) {
      /keypress ${TurnKey} hold
      /varset IsTurning 1
   }
   /goto :TurnLoop

/return 