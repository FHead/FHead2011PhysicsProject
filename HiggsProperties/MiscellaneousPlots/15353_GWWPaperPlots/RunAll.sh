source Utilities.sh

mkdir -p Plot
mkdir -p Tem

FCompileAll

FPrepareFigureC
# FPrepareFigureE
FPrepareFigureF
# FPrepareFigureG
FPrepareFigureGPart2
FPrepareFigureH
FPrepareFigureL
FPrepareFigureM

# FRunFigureA   # Cool plots
FRunFigureB   # Sensitivity vs. N/L
FRunFigureC   # Fixed yt, sigma
# FRunFigureD   # example likelihood
# FRunFigureE   # Minimize yt, p-value
FRunFigureF   # Integrated yt, p-value
FRunFigureG   # Integrated yt, sigma
              # Fixed yt, p-value
FRunFigureI   # Final plot sigma
FRunFigureJ   # Final plot p-value
FRunFigureK   # Final plot sensitivity
# FRunFigureL   # Hypothesis testing plots
# FRunFigureM   # Separation plots
# FRunFigureN   # Hypothesis testing final (?) plots
FRunFigureO   # Separation final plots

FUpload


