library(ROCR)
library(yaml)

perf.average <- function(perf) {
## replace inf with max + mean of differences
 if (length(perf@alpha.values)!=0) perf@alpha.values <-
        lapply(perf@alpha.values,
               function(x) { isfin <- is.finite(x);
                             x[is.infinite(x)] <-
                               (max(x[isfin]) +
                                mean(abs(x[isfin][-1] -
                                         x[isfin][-length(x[isfin])])));
                             x } )
      ## remove samples with x or y not finite
      for (i in 1:length(perf@x.values)) {
          ind.bool <- (is.finite(perf@x.values[[i]]) &
                       is.finite(perf@y.values[[i]]))

          if (length(perf@alpha.values)>0)
            perf@alpha.values[[i]] <- perf@alpha.values[[i]][ind.bool]

          perf@x.values[[i]] <- perf@x.values[[i]][ind.bool]
          perf@y.values[[i]] <- perf@y.values[[i]][ind.bool]
      }

  perf.sampled <- perf
  alpha.values <- rev(seq(min(unlist(perf@alpha.values)),
                          max(unlist(perf@alpha.values)),
                          length=max( sapply(perf@alpha.values, length))))
  for (i in 1:length(perf.sampled@y.values)) {
      perf.sampled@x.values[[i]] <-
        approxfun(perf@alpha.values[[i]],perf@x.values[[i]],
                  rule=2, ties=mean)(alpha.values)
      perf.sampled@y.values[[i]] <-
        approxfun(perf@alpha.values[[i]], perf@y.values[[i]],
                  rule=2, ties=mean)(alpha.values)
  }

  ## compute average curve
  perf.avg <- perf.sampled
  browser()
  perf.avg@x.values <- list( rowMeans( data.frame( perf.avg@x.values)))
  perf.avg@y.values <- list(rowMeans( data.frame( perf.avg@y.values)))
  perf.avg@alpha.values <- list( alpha.values )

  perf.avg
}

perf.avg <- perf.rocr.pr.avg
testseq <- test.numseq(
            min(unlist(perf.avg@alpha.values)),
            max(unlist(perf.avg@alpha.values)),
            length(unlist(perf.avg@alpha.values)))
cbind(rev(testseq), unlist(perf.avg@alpha.values))
cbind(perf.rnr.raw$perf_pr$alpha_values, unlist(perf.avg@alpha.values))


data(ROCR.xval)

pred.rocr <- prediction(ROCR.xval$predictions, ROCR.xval$labels)
perf.rocr.pr <- performance(pred.rocr, "ppv", "tpr")
perf.rocr.pr.avg <- perf.average(perf.rocr.pr)

perf.rnr.raw <- yaml.load_file("../src/z")

perf.rnr.pr <- new("performance",
    x.name="Recall",
    y.name="Precision",
    alpha.name="Cutoff",
    x.values=list(perf.rnr.raw$perf_pr$x_values),
    y.values=list(perf.rnr.raw$perf_pr$y_values),
    alpha.values=list(perf.rnr.raw$perf_pr$alpha_values)
)

pdf("avg_cmp_rocr-rnr.pdf", width=30, height=30)
plot(perf.rocr.pr.avg, xlim=c(0,1), ylim=c(0,1))
plot(perf.rnr.pr, col="red", add=TRUE)

plot(perf.rnr.pr, xlim=c(0,1), ylim=c(0,1))
plot(perf.rocr.pr.avg, col="red", add=TRUE)
dev.off()

