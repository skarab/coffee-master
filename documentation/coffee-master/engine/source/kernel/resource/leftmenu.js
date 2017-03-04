function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6323\" class=\"headerLeftMenuInActive\"><a id=\"aID6323\" href=\"#\" OnMouseOver=\"link('_dir','resource0',this)\" class=\"leftMenuLinkHeadInActive\">resource</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6315\" class=\"leftMenuInActive\"><a id=\"aID6315\" href=\"#\" OnMouseOver=\"link('_dir','chunk/chunk0',this)\" class=\"leftMenuLinkInActive\">chunk</a></div>\n");
document.write("<div id=\"divID6316\" class=\"leftMenuInActive\"><a id=\"aID6316\" href=\"#\" OnMouseOver=\"link('_dir','handler/handler0',this)\" class=\"leftMenuLinkInActive\">handler</a></div>\n");
document.write("<div id=\"divID6317\" class=\"leftMenuInActive\"><a id=\"aID6317\" href=\"#\" OnMouseOver=\"link('_dir','library/library0',this)\" class=\"leftMenuLinkInActive\">library</a></div>\n");
document.write("<div id=\"divID6318\" class=\"leftMenuInActive\"><a id=\"aID6318\" href=\"#\" OnMouseOver=\"link('_dir','lod/lod0',this)\" class=\"leftMenuLinkInActive\">lod</a></div>\n");
document.write("<div id=\"divID6319\" class=\"leftMenuInActive\"><a id=\"aID6319\" href=\"#\" OnMouseOver=\"link('_dir','macros/macros0',this)\" class=\"leftMenuLinkInActive\">macros</a></div>\n");
document.write("<div id=\"divID6320\" class=\"leftMenuInActive\"><a id=\"aID6320\" href=\"#\" OnMouseOver=\"link('_dir','mode/mode0',this)\" class=\"leftMenuLinkInActive\">mode</a></div>\n");
document.write("<div id=\"divID6321\" class=\"leftMenuInActive\"><a id=\"aID6321\" href=\"#\" OnMouseOver=\"link('_dir','process/process0',this)\" class=\"leftMenuLinkInActive\">process</a></div>\n");
document.write("<div id=\"divID6322\" class=\"leftMenuInActive\"><a id=\"aID6322\" href=\"#\" OnMouseOver=\"link('_dir','property/property0',this)\" class=\"leftMenuLinkInActive\">property</a></div>\n");
document.write("<div id=\"divID6324\" class=\"leftMenuInActive\"><a id=\"aID6324\" href=\"#\" OnMouseOver=\"link('_dir','state/state0',this)\" class=\"leftMenuLinkInActive\">state</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID806\" class=\"leftMenuInActive\"><a id=\"aID806\" href=\"#\" OnMouseOver=\"link('_class','Manager24579',this)\" class=\"leftMenuLinkInActive\">Manager</a></div>\n");
document.write("<div id=\"divID807\" class=\"leftMenuInActive\"><a id=\"aID807\" href=\"#\" OnMouseOver=\"link('_class','Object24579',this)\" class=\"leftMenuLinkInActive\">Object</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
