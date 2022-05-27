% SCRYCLI(1) scrycli 0.1
% Sebastien MacDougall-Landry
% May 2022

# NAME
scrycli - get Magic: The Gathering card data on the terminal

# SYNOPSIS
**scrycli** *[OPTION...]* *SEARCH...*

# DESCRIPTION
**scrycli** uses libscry to fetch card data from Scryfall and cache it. Works as a terminal counterpart to the Scryfall website.

# OPTIONS
**-i**
: Shows the image of the resulting card(s) in the terminal. Looks best in kitty. Will have different behaviour depending on what mode is used.

# EXAMPLES
**scrycli -i vannifar**
: Outputs just the card Prime Speaker Vannifar, with image.

**scrycli color=g type:legendary type:creature legal:commander**
: Outputs all legal mono-green commanders.

**scrycli is:funny**
: Outputs all funny cards.

The full Scryfall syntax can be found at https://scryfall.com/docs/syntax

# EXIT VALUES
Scrycli will usually exit with 0 unless you encounter a bug.


# BUGS
Images are displayed in a very unsophisticated way

# COPYRIGHT
Copyright © 2022 Sebastien MacDougall-Landry. License GPLv3+: GNU GPL version 3 or later . This is free software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law.
