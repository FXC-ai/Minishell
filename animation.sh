#!/bin/bash

# Nombre d'images à générer
frames=30

# Génération des images
for i in $(seq 1 $frames); do
  pct=$((i * 100 / frames))
  
  # Position et taille de "terminal"
  tx=$((100 - pct))
  ty=$((100 + pct))
  tw=$((100 + pct / 2))
  th=$((100 + pct / 2))

  # Position et taille de "titan"
  ttx=$((100 - pct * 3))
  tty=$((100 + pct * 3))
  ttw=$((100 + pct * 2))
  tth=$((100 + pct * 2))

  convert -size 400x400 xc:skyblue \
    -font "Arial-Bold" -pointsize 48 -fill black \
    -annotate +${tx}+${ty} "terminal" \
    -annotate +${ttx}+${tty} "titan" \
    -resize ${tw}x${th}\! -gravity center -crop 400x400+0+0 \
    -flatten frame$(printf "%02d" $i).png
done

# Création du fichier GIF animé
convert -delay 10 -loop 0 frame*.png animation.gif

# Suppression des images temporaires
rm frame*.png
