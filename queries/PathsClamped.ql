/**
 * @name Entry-point length to memcpy length, clamps as barriers
 * @description The same paths with every node on a line marked clamp as a barrier.
 * @kind path-problem
 * @problem.severity warning
 * @id fixtures/paths-clamped
 */

import Fixtures

module Config implements DataFlow::ConfigSig {
  predicate isSource(DataFlow::Node source) { fixtureSource(source) }

  predicate isSink(DataFlow::Node sink) { fixtureSink(sink) }

  predicate isBarrier(DataFlow::Node node) { onMarkedLine(node, "/* clamp */") }
}

module Flow = TaintTracking::Global<Config>;

import Flow::PathGraph

from Flow::PathNode source, Flow::PathNode sink
where Flow::flowPath(source, sink)
select sink.getNode(), source, sink, "Length from $@ reaches this copy.", source.getNode(),
  source.getNode().getFunction().getName()
