library(yaml)
library(ROCR)

b2g.ref <- readRDS("../../2013-05-01/pr.avg.cv.go.b2g.rds.gz")
z <- yaml.load_file("z")
pdf("testc.pdf")
plot(z$perf_pr$x_values, z$perf_pr$y_values, xlim=c(0,1), ylim=c(0,1), type="l")
lines(unlist(b2g.ref@x.values), unlist(b2g.ref@y.values), col="red")
dev.off()
