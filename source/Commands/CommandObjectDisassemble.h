//===-- CommandObjectDisassemble.h ------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_CommandObjectDisassemble_h_
#define liblldb_CommandObjectDisassemble_h_

// C Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "lldb/Core/ArchSpec.h"
#include "lldb/Interpreter/CommandObject.h"
#include "lldb/Interpreter/Options.h"

namespace lldb_private {

//-------------------------------------------------------------------------
// CommandObjectDisassemble
//-------------------------------------------------------------------------

class CommandObjectDisassemble : public CommandObjectParsed {
public:
  class CommandOptions : public Options {
  public:
    CommandOptions();

    ~CommandOptions() override;

    Error SetOptionValue(uint32_t option_idx, const char *option_arg,
                         ExecutionContext *execution_context) override;

    void OptionParsingStarting(ExecutionContext *execution_context) override;

    const OptionDefinition *GetDefinitions() override;

    const char *GetPluginName() {
      return (plugin_name.empty() ? nullptr : plugin_name.c_str());
    }

    const char *GetFlavorString() {
      if (flavor_string.empty() || flavor_string == "default")
        return nullptr;
      return flavor_string.c_str();
    }

    Error OptionParsingFinished(ExecutionContext *execution_context) override;

    bool show_mixed; // Show mixed source/assembly
    bool show_bytes;
    uint32_t num_lines_context;
    uint32_t num_instructions;
    bool raw;
    std::string func_name;
    bool current_function;
    lldb::addr_t start_addr;
    lldb::addr_t end_addr;
    bool at_pc;
    bool frame_line;
    std::string plugin_name;
    std::string flavor_string;
    ArchSpec arch;
    bool some_location_specified; // If no location was specified, we'll select
                                  // "at_pc".  This should be set
    // in SetOptionValue if anything the selects a location is set.
    lldb::addr_t symbol_containing_addr;
    static OptionDefinition g_option_table[];
  };

  CommandObjectDisassemble(CommandInterpreter &interpreter);

  ~CommandObjectDisassemble() override;

  Options *GetOptions() override { return &m_options; }

protected:
  bool DoExecute(Args &command, CommandReturnObject &result) override;

  CommandOptions m_options;
};

} // namespace lldb_private

#endif // liblldb_CommandObjectDisassemble_h_
