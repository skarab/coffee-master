function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6475\" class=\"headerLeftMenuInActive\"><a id=\"aID6475\" href=\"#\" OnMouseOver=\"link('_dir','source0',this)\" class=\"leftMenuLinkHeadInActive\">source</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6467\" class=\"leftMenuInActive\"><a id=\"aID6467\" href=\"#\" OnMouseOver=\"link('_dir','asset/asset0',this)\" class=\"leftMenuLinkInActive\">asset</a></div>\n");
document.write("<div id=\"divID6476\" class=\"leftMenuInActive\"><a id=\"aID6476\" href=\"#\" OnMouseOver=\"link('_dir','component/component0',this)\" class=\"leftMenuLinkInActive\">component</a></div>\n");
document.write("<div id=\"divID6477\" class=\"leftMenuInActive\"><a id=\"aID6477\" href=\"#\" OnMouseOver=\"link('_dir','config/config0',this)\" class=\"leftMenuLinkInActive\">config</a></div>\n");
document.write("<div id=\"divID6478\" class=\"leftMenuInActive\"><a id=\"aID6478\" href=\"#\" OnMouseOver=\"link('_dir','document/document0',this)\" class=\"leftMenuLinkInActive\">document</a></div>\n");
document.write("<div id=\"divID6481\" class=\"leftMenuInActive\"><a id=\"aID6481\" href=\"#\" OnMouseOver=\"link('_dir','project/project0',this)\" class=\"leftMenuLinkInActive\">project</a></div>\n");
document.write("<div id=\"divID6499\" class=\"leftMenuInActive\"><a id=\"aID6499\" href=\"#\" OnMouseOver=\"link('_dir','widget/widget0',this)\" class=\"leftMenuLinkInActive\">widget</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1072\" class=\"leftMenuInActive\"><a id=\"aID1072\" href=\"#\" OnMouseOver=\"link('_class','Application38803',this)\" class=\"leftMenuLinkInActive\">Application</a></div>\n");
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
