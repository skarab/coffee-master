function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6337\" class=\"headerLeftMenuInActive\"><a id=\"aID6337\" href=\"#\" OnMouseOver=\"link('_dir','storage0',this)\" class=\"leftMenuLinkHeadInActive\">storage</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6331\" class=\"leftMenuInActive\"><a id=\"aID6331\" href=\"#\" OnMouseOver=\"link('_dir','data/data0',this)\" class=\"leftMenuLinkInActive\">data</a></div>\n");
document.write("<div id=\"divID6332\" class=\"leftMenuInActive\"><a id=\"aID6332\" href=\"#\" OnMouseOver=\"link('_dir','file/file0',this)\" class=\"leftMenuLinkInActive\">file</a></div>\n");
document.write("<div id=\"divID6334\" class=\"leftMenuInActive\"><a id=\"aID6334\" href=\"#\" OnMouseOver=\"link('_dir','logical/logical0',this)\" class=\"leftMenuLinkInActive\">logical</a></div>\n");
document.write("<div id=\"divID6335\" class=\"leftMenuInActive\"><a id=\"aID6335\" href=\"#\" OnMouseOver=\"link('_dir','pack/pack0',this)\" class=\"leftMenuLinkInActive\">pack</a></div>\n");
document.write("<div id=\"divID6336\" class=\"leftMenuInActive\"><a id=\"aID6336\" href=\"#\" OnMouseOver=\"link('_dir','physical/physical0',this)\" class=\"leftMenuLinkInActive\">physical</a></div>\n");
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
