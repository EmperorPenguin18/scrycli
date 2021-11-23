% SCRYCLI(1) scrycli 0.1
% Sebastien MacDougall-Landry
% November 2021

# NAME
scrycli - get Magic: The Gathering card data on the terminal

# SYNOPSIS
**scrycli** *SEARCH*

# DESCRIPTION
**scrycli** uses libscry to fetch card data from Scryfall and cache it. Works as a terminal counterpart to the Scryfall website.

# EXAMPLES
**scrycli vannifar**
: Outputs just the card Prime Speaker Vannifar.

**scrycli color=g+type:legendary+type:creature+legal:commander**
: Outputs all legal mono-green commanders.

**scrycli is:funny**
: Outputs all funny cards.

The full Scryfall syntax can be found at https://scryfall.com/docs/syntax

# EXIT VALUES
Scrycli will usually exit with 0 unless you encounter a bug.


# BUGS
If there are no results to your search, the program crashes.

# COPYRIGHT
Copyright © 2021 Sebastien MacDougall-Landry. License GPLv3+: GNU GPL version 3 or later . This is free software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law.
