/** Sources and sinks of the fixtures: the length parameter `n` of each fN_entry, and the length argument of memcpy. */

import cpp
import semmle.code.cpp.dataflow.new.DataFlow
import semmle.code.cpp.dataflow.new.TaintTracking

predicate fixtureSource(DataFlow::Node source) {
  exists(Parameter p |
    p = source.asParameter() and
    p.getName() = "n" and
    p.getFunction().getName().regexpMatch("f[0-9]+_entry")
  )
}

predicate fixtureSink(DataFlow::Node sink) {
  exists(FunctionCall copy |
    copy.getTarget().hasGlobalName("memcpy") and
    sink.asExpr() = copy.getArgument(2)
  )
}

/** A node on a line the fixture marks with the given comment. */
predicate onMarkedLine(DataFlow::Node node, string marker) {
  exists(Comment c, Location l |
    c.getContents() = marker and
    l = node.getLocation() and
    l.getFile() = c.getFile() and
    l.getStartLine() = c.getLocation().getStartLine()
  )
}
