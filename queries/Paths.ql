/**
 * @name Entry-point length to memcpy length
 * @description Every path from an entry point's length parameter to a memcpy length, no barriers.
 * @kind path-problem
 * @problem.severity warning
 * @id fixtures/paths
 */

import Fixtures

module Config implements DataFlow::ConfigSig {
  predicate isSource(DataFlow::Node source) { fixtureSource(source) }

  predicate isSink(DataFlow::Node sink) { fixtureSink(sink) }
}

module Flow = TaintTracking::Global<Config>;

import Flow::PathGraph

from Flow::PathNode source, Flow::PathNode sink
where Flow::flowPath(source, sink)
select sink.getNode(), source, sink, "Length from $@ reaches this copy.", source.getNode(),
  source.getNode().getFunction().getName()
