# T06 – Find or Create a Session (`findOrCreateSession`)

- Assignee: Kiên
- Reviewer: Triển

## 1. Function specification

- Proposed function signature:
```cpp
int findOrCreateSession(Session sessions[], int& sessionCount, const string& id);
```

### Input
- `sessions`: the array that stores all sessions created so far
- `sessionCount`: the number of sessions currently stored in `sessions`
- `id`: the value that identifies one session (taken from the event being processed)

### Output
- If a session with this `id` already exists: return its index. `sessionCount` is unchanged
- If no session has this `id`: create a new session at index `sessionCount`,
  increase `sessionCount` by 1, and return the index of the new session
- If a new session is needed but the array is full: return `-1`.
  The caller must not use the result as an index when it is `-1`

### Scope
- Only find a session or create an empty one
- Do not apply the event to the session; this is done by `applyEvent()`
- Do not read CSV files or validate the event; this is handled in T05
- Do not compute dwell time; this is handled in T07

## 2. Pseudocode

Conventions:
- Array indices start at 0.
- REFERENCE parameters allow the function to modify the caller's variables.
- `MAX_SESSIONS` is the size of the `sessions` array.

```text
FUNCTION findOrCreateSession(sessions, REFERENCE sessionCount, id)

    i ← 0

    WHILE i < sessionCount
        IF sessions[i].id = id THEN
            RETURN i
        END IF

        i ← i + 1
    END WHILE

    IF sessionCount = MAX_SESSIONS THEN
        RETURN -1
    END IF

    sessions[sessionCount].id ← id
    set all other fields of sessions[sessionCount] to their initial values
    sessionCount ← sessionCount + 1

    RETURN sessionCount - 1

END FUNCTION
```
## 3.Flowchart
<img width="657" height="842" alt="T06-find-or-create-session" src="https://github.com/user-attachments/assets/23c4542a-827e-412c-a830-b33bef1d7436" />

```
