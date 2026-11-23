package sample;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/** Logs incoming requests, including the caller-supplied user agent. */
public final class RequestLog {
    private static final Logger LOG = LogManager.getLogger(RequestLog.class);

    private RequestLog() {}

    public static void record(String path, String userAgent) {
        LOG.info("request path={} userAgent={}", path, userAgent);
    }

    public static void main(String[] args) {
        String path = args.length > 0 ? args[0] : "/";
        String userAgent = args.length > 1 ? args[1] : "unknown";
        record(path, userAgent);
    }
}
